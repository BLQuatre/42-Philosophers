/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cauvray <cauvray@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 23:03:06 by cauvray           #+#    #+#             */
/*   Updated: 2025/06/27 03:49:36 by cauvray          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	check_death(t_philo *arg)
{
	int		i;

	i = -1;
	sem_wait(arg->sem_refresh);
	if (get_time_since(arg->eating_time) >= arg->info[time_to_die])
	{
		sem_wait(arg->sem_print);
		printf("%ld %d died\n",
			get_time_since(arg->init_time), arg->i + 1);
		arg->is_dead = 1;
		while (++i < arg->info[philo_n])
			sem_post(arg->sem_eat);
		sem_post(arg->sem_death);
	}
	sem_post(arg->sem_refresh);
}

void	*monitor(void *philo)
{
	t_philo	*arg;
	int		j;

	j = 0;
	arg = (t_philo *)philo;
	while (1)
	{
		check_death(arg);
		sem_wait(arg->sem_refresh);
		if (arg->info[nb_meals]
			&& arg->nb_meals == arg->info[nb_meals] && ++j == 1)
			sem_post(arg->sem_eat);
		sem_post(arg->sem_refresh);
		usleep(100);
	}
	return (NULL);
}

void	philo_routine(t_philo *arg)
{
	while (get_time() <= arg->init_time)
		usleep(200);
	arg->eating_time = get_time();
	pthread_create(&arg->th, NULL, monitor, arg);
	action_think(arg);
	if (arg->i % 2)
		smart_sleep(arg, arg->info[eat_time] / 2);
	while (1)
	{
		sem_wait(arg->sem);
		take_fork(arg);
		if (arg->info[philo_n] > 1)
		{
			start_eating(arg);
			sem_wait(arg->sem_print);
			printf("%ld %d is sleeping\n",
				get_time_since(arg->init_time), arg->i + 1);
			sem_post(arg->sem_print);
			smart_sleep(arg, arg->info[sleep_time]);
			sem_wait(arg->sem_print);
			printf("%ld %d is thinking\n",
				get_time_since(arg->init_time), arg->i + 1);
			sem_post(arg->sem_print);
		}
	}
}

void	init_philosophers(t_philo *philo)
{
	int	pid;
	int	i;

	i = -1;
	philo->is_dead = 0;
	while (++i < philo->info[philo_n])
	{
		philo->i = i;
		pid = fork();
		if (pid == -1)
			return ;
		if (pid == 0)
			philo_routine(philo);
		if (pid > 0)
			philo->ids[i] = pid;
	}
	i = -1;
	if (philo->info[nb_meals])
		while (++i < philo->info[philo_n])
			sem_wait(philo->sem_eat);
	else
		sem_wait(philo->sem_death);
	i = -1;
	while (++i < philo->info[philo_n])
		kill(philo->ids[i], SIGKILL);
}
