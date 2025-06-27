/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cauvray <cauvray@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 23:03:06 by cauvray           #+#    #+#             */
/*   Updated: 2025/06/27 03:45:30 by cauvray          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	init_dinner(t_philo *philo)
{
	philo->ids = malloc(sizeof(int) * philo->info[philo_n]);
	if (!philo->ids)
		return (0);
	sem_unlink("/FORKS");
	sem_unlink("/EAT");
	sem_unlink("/DEATH");
	sem_unlink("/LTE");
	sem_unlink("/PRINT");
	philo->sem = sem_open("/FORKS", O_CREAT | O_EXCL, 0644,
			philo->info[philo_n]);
	philo->sem_eat = sem_open("/EAT", O_CREAT | O_EXCL, 0644, 0);
	philo->sem_death = sem_open("/DEATH", O_CREAT | O_EXCL, 0644, 0);
	philo->sem_refresh = sem_open("/LTE", O_CREAT | O_EXCL, 0644, 1);
	philo->sem_print = sem_open("/PRINT", O_CREAT | O_EXCL, 0644, 1);
	philo->init_time = get_time() + 300;
	philo->is_dead = 0;
	philo->nb_meals = 0;
	philo->eating_time = 0;
	return (1);
}
