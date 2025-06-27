/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cauvray <cauvray@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 23:03:06 by cauvray           #+#    #+#             */
/*   Updated: 2025/06/26 23:28:06 by cauvray          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	action_sleep(t_philo *philo)
{
	log_action(philo, "is sleeping");
	smart_sleep(philo->dinner->sleep_time, philo->dinner);
}

void	action_think(t_philo *philo)
{
	log_action(philo, "is thinking");
}

bool	action_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->dinner->forks[philo->forks[1]]);
	log_action(philo, "has taken a fork");
	if (philo->dinner->nb_philo == 1)
	{
		pthread_mutex_unlock(&philo->dinner->forks[0]);
		smart_sleep(philo->dinner->die_time, philo->dinner);
		return (false);
	}
	pthread_mutex_lock(&philo->dinner->forks[philo->forks[0]]);
	log_action(philo, "has taken a fork");
	log_action(philo, "is eating");
	pthread_mutex_lock(&philo->dinner->lock_eat);
	philo->last_meal = get_time();
	philo->nb_meals++;
	pthread_mutex_unlock(&philo->dinner->lock_eat);
	smart_sleep(philo->dinner->eat_time, philo->dinner);
	pthread_mutex_unlock(&philo->dinner->forks[philo->forks[0]]);
	pthread_mutex_unlock(&philo->dinner->forks[philo->forks[1]]);
	return (true);
}
