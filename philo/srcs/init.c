/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cauvray <cauvray@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 23:03:06 by cauvray           #+#    #+#             */
/*   Updated: 2025/06/26 23:28:23 by cauvray          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static pthread_mutex_t	*init_forks(t_dinner *dinner)
{
	pthread_mutex_t	*fork;
	int				i;

	fork = malloc(sizeof(pthread_mutex_t) * dinner->nb_philo);
	if (!fork)
		return (printf(ERR_MEMORY), NULL);
	i = -1;
	while (++i < dinner->nb_philo)
	{
		if (pthread_mutex_init(&fork[i], NULL))
			return (printf(ERR_MUT_INIT), destroy_mutex(fork, i), NULL);
	}
	return (fork);
}

static void	init_philosophers(t_dinner *dinner)
{
	int	i;

	i = -1;
	while (++i < dinner->nb_philo)
	{
		dinner->philo[i].id = i + 1;
		dinner->philo[i].nb_meals = 0;
		dinner->philo[i].dinner = dinner;
		dinner->philo[i].forks[0] = i;
		dinner->philo[i].forks[1] = i - 1;
		if (i == 0)
			dinner->philo[i].forks[1] = dinner->nb_philo - 1;
	}
}

bool	init_mutex(t_dinner *dinner)
{
	if (pthread_mutex_init(&dinner->lock_eat, NULL))
		return (crash(ERR_MUT_INIT, dinner), false);
	if (pthread_mutex_init(&dinner->lock_death, NULL))
	{
		pthread_mutex_destroy(&dinner->lock_eat);
		return (crash(ERR_MUT_INIT, dinner), false);
	}
	if (pthread_mutex_init(&dinner->lock_write, NULL))
	{
		pthread_mutex_destroy(&dinner->lock_eat);
		pthread_mutex_destroy(&dinner->lock_death);
		return (crash(ERR_MUT_INIT, dinner), false);
	}
	return (true);
}

bool	init_dinner(t_dinner *dinner)
{
	dinner->philo = malloc(sizeof(t_philo) * dinner->nb_philo);
	if (!dinner->philo)
		return (printf(ERR_MEMORY), false);
	init_philosophers(dinner);
	dinner->forks = init_forks(dinner);
	dinner->death_flag = false;
	if (!dinner->forks)
		return (false);
	if (!init_mutex(dinner))
		return (false);
	return (true);
}
