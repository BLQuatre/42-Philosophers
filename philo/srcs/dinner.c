/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cauvray <cauvray@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 23:03:06 by cauvray           #+#    #+#             */
/*   Updated: 2025/06/26 23:28:13 by cauvray          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	valid_action(t_philo *philo, bool condition)
{
	bool	status;

	status = false;
	if (condition == false)
	{
		pthread_mutex_lock(&philo->dinner->lock_death);
		if (philo->dinner->death_flag == true)
			status = true;
		pthread_mutex_unlock(&philo->dinner->lock_death);
		return (status);
	}
	else
	{
		if (philo->dinner->nb_meals < 0)
			return (false);
		if (philo->nb_meals < philo->dinner->nb_meals)
			return (false);
	}
	return (true);
}

void	*philosophers(void *arg)
{
	t_philo	*philo;

	if (!arg)
		return (NULL);
	philo = (t_philo *) arg;
	if (philo->id % 2 == 0)
		smart_sleep(philo->dinner->eat_time / 2, philo->dinner);
	while (!valid_action(philo, false) && !valid_action(philo, true))
	{
		action_think(philo);
		if (!action_eat(philo))
			return (NULL);
		action_sleep(philo);
	}
	return (NULL);
}

static void	set_time(t_dinner *dinner)
{
	int	i;

	i = -1;
	while (++i < dinner->nb_philo)
	{
		dinner->philo[i].birth = get_time();
		dinner->philo[i].last_meal = get_time();
	}
}

static bool	philo_create(t_dinner *dinner)
{
	int	i;

	i = -1;
	set_time(dinner);
	if (pthread_create(&dinner->monitor, NULL, monitor, dinner))
		return (crash(ERR_PTH_INIT, dinner), false);
	while (++i < dinner->nb_philo)
		if (pthread_create(&dinner->philo[i].thread, NULL,
				&philosophers, &dinner->philo[i]))
			return (crash(ERR_PTH_INIT, dinner), false);
	i = -1;
	if (pthread_join(dinner->monitor, NULL))
		return (crash(ERR_PTH, dinner), false);
	while (++i < dinner->nb_philo)
		if (pthread_join(dinner->philo[i].thread, NULL))
			return (crash(ERR_PTH, dinner), false);
	return (true);
}

bool	start_dinner(t_dinner *dinner)
{
	if (!dinner->nb_meals)
		return (false);
	if (!philo_create(dinner))
		return (false);
	return (true);
}
