/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cauvray <cauvray@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 23:03:06 by cauvray           #+#    #+#             */
/*   Updated: 2025/06/27 04:47:25 by cauvray          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static bool	check_fulfilled(t_philo *philo, t_dinner *dinner, t_args *args)
{
	bool	res ;

	sem_wait(dinner->update);
	res = philo->nb_time_ate == args->nb_time_must_eat ;
	sem_post(dinner->update);
	return (res);
}

static bool	check_dead(t_philo *philo, t_dinner *dinner, t_args *args)
{
	bool	res ;

	sem_wait(dinner->update);
	res = get_time_since(philo->last_meal) > args->time_to_die ;
	sem_post(dinner->update);
	return (res);
}

static bool	meal_shall_continue(t_philo *philo, t_dinner *dinner, t_args *args)
{
	bool	res ;

	sem_wait(dinner->update);
	res = dinner->death->__align != 0 ;
	sem_post(dinner->update);
	res = res && !check_dead(philo, dinner, args)
		&& !check_fulfilled(philo, dinner, args);
	return (res);
}

static void	*mini_monitoring(void *param)
{
	t_philo	*philo ;
	t_dinner	*dinner ;
	t_args	*args ;

	philo = (t_philo *) param ;
	dinner = philo->dinner ;
	args = philo->args ;
	while (true)
	{
		if (check_dead(philo, dinner, args))
		{
			display_action(philo, dinner, "died \a");
			sem_wait(dinner->update);
			dinner->death->__align = 0 ;
			sem_post(dinner->update);
		}
		sem_wait(dinner->update);
		if (dinner->death->__align == 0)
			return (sem_post(dinner->update), NULL);
		sem_post(dinner->update);
		if (check_fulfilled(philo, dinner, args))
			return (NULL);
	}
	return (NULL);
}

void	philosophing(t_philo **philos, int index, t_dinner *dinner, t_args *args)
{
	t_philo		*philo ;
	pthread_t	thread ;

	philo = philos[index];
	thread = 0 ;
	if (pthread_create(&thread, NULL, mini_monitoring, philo) != 0)
		(error_pthread(dinner), free_all(philos, dinner, args), exit(1));
	if (args->nb_philo == 1)
	{
		(sem_wait(dinner->forks), display_action(philo, dinner, "has taken a fork"));
		(smart_sleep(philo->args->time_to_die + 100), sem_post(dinner->forks));
	}
	if (philo->id % 2 == 0)
		smart_sleep(philo->args->time_to_eat / 2);
	while (meal_shall_continue(philo, dinner, args))
	{
		action_eat(philo, dinner);
		action_sleep_think(philo, dinner);
	}
	pthread_join(thread, NULL);
	free_all(philos, dinner, args);
	exit(0);
}
