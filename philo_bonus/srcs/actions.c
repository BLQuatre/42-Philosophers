/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cauvray <cauvray@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 23:03:06 by cauvray           #+#    #+#             */
/*   Updated: 2025/06/27 03:37:36 by cauvray          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	action_think(t_philo *arg)
{
	sem_wait(arg->sem_print);
	printf("%ld %d is thinking\n",
		get_time_since(arg->init_time),
		arg->i + 1);
	sem_post(arg->sem_print);
}

void	take_fork(t_philo *arg)
{
	sem_wait(arg->sem_print);
	printf("%ld %d has taken a fork\n",
		get_time_since(arg->init_time),
		arg->i + 1);
	sem_post(arg->sem_print);
}

void	action_eat(t_philo *arg)
{
	sem_wait(arg->sem_print);
	printf("%ld %d is eating\n",
		get_time_since(arg->init_time),
		arg->i + 1);
	sem_post(arg->sem_print);
}

void	start_eating(t_philo *arg)
{
	sem_wait(arg->sem);
	take_fork(arg);
	sem_wait(arg->sem_refresh);
	arg->eating_time = get_time();
	sem_post(arg->sem_refresh);
	action_eat(arg);
	smart_sleep(arg, arg->info[eat_time]);
	sem_wait(arg->sem_refresh);
	if (arg->info[nb_meals])
		arg->nb_meals++;
	sem_post(arg->sem_refresh);
	sem_post(arg->sem);
	sem_post(arg->sem);
}
