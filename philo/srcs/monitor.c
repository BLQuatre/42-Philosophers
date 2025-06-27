/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cauvray <cauvray@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 23:03:06 by cauvray           #+#    #+#             */
/*   Updated: 2025/06/26 23:28:29 by cauvray          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	is_dead(t_philo *philo)
{
	long long	last_meal;
	bool		status;

	pthread_mutex_lock(&philo->dinner->lock_eat);
	last_meal = get_time() - philo->last_meal;
	pthread_mutex_unlock(&philo->dinner->lock_eat);
	status = false;
	if (last_meal >= philo->dinner->die_time)
		status = true;
	return (status);
}

static bool	check_death(t_philo *philo)
{
	int	i;

	i = -1;
	while (++i < philo[0].dinner->nb_philo)
	{
		if (is_dead(&philo[i]))
		{
			log_action(&philo[i], "died");
			pthread_mutex_lock(&philo->dinner->lock_death);
			philo->dinner->death_flag = true;
			pthread_mutex_unlock(&philo->dinner->lock_death);
			return (true);
		}
		usleep(100);
	}
	return (false);
}

static bool	check_nb_meals(t_philo *philo)
{
	int	full;
	int	i;

	full = 0;
	i = 0;
	if (philo->dinner->nb_meals == -1)
		return (false);
	while (i < philo[0].dinner->nb_philo)
	{
		pthread_mutex_lock(&philo->dinner->lock_eat);
		if (philo[i].nb_meals >= philo[0].dinner->nb_meals)
			full++;
		pthread_mutex_unlock(&philo[0].dinner->lock_eat);
		i++;
		usleep(100);
	}
	if (full == philo[0].dinner->nb_philo)
	{
		pthread_mutex_lock(&philo->dinner->lock_death);
		philo->dinner->death_flag = true;
		pthread_mutex_unlock(&philo->dinner->lock_death);
		return (true);
	}
	return (false);
}

void	*monitor(void *arg)
{
	t_dinner	*dinner;

	dinner = (t_dinner *)arg;
	while (true)
		if (check_death(dinner->philo)
			|| check_nb_meals(dinner->philo))
			break ;
	return (arg);
}
