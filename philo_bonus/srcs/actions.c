/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cauvray <cauvray@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 23:03:06 by cauvray           #+#    #+#             */
/*   Updated: 2025/06/27 04:49:38 by cauvray          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	display_action(t_philo *philo, t_dinner *dinner, char *msg)
{
	sem_wait(dinner->update);
	if (dinner->death->__align == 1)
	{
		sem_wait(dinner->display);
		printf("%ld %d %s \n",
			get_time_since(dinner->lunch_start), philo->id, msg);
		sem_post(dinner->display);
	}
	sem_post(dinner->update);
}

void	action_eat(t_philo *philo, t_dinner *dinner)
{
	if (sem_wait(dinner->forks) == 0)
	{
		display_action(philo, dinner, "has taken a fork");
		usleep(200);
		if (sem_wait(dinner->forks) == 0)
		{
			display_action(philo, dinner, "has taken a fork");
			display_action(philo, dinner, "is eating");
			smart_sleep(philo->args->time_to_eat);
			sem_wait(dinner->update);
			philo->last_meal = get_time_in_ms();
			philo->nb_time_ate++ ;
			sem_post(dinner->update);
			sem_post(dinner->forks);
		}
		sem_post(dinner->forks);
	}
}

void	action_sleep_think(t_philo *philo, t_dinner *dinner)
{
	display_action(philo, dinner, "is sleeping");
	smart_sleep(philo->args->time_to_sleep);
	display_action(philo, dinner, "is thinking");
}
