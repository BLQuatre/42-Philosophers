/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cauvray <cauvray@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 23:03:06 by cauvray           #+#    #+#             */
/*   Updated: 2025/06/26 23:28:33 by cauvray          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	unlock_mutex(t_dinner *dinner)
{
	int	i;

	i = -1;
	while (++i < dinner->nb_philo)
		pthread_mutex_unlock(&dinner->forks[i]);
	pthread_mutex_unlock(&dinner->lock_death);
	pthread_mutex_unlock(&dinner->lock_eat);
	pthread_mutex_unlock(&dinner->lock_write);
}

void	destroy_mutex(pthread_mutex_t *mtx, int max)
{
	int	i;

	i = -1;
	while (++i < max)
	{
		if (pthread_mutex_destroy(&mtx[i]))
			return ((void) printf(ERR_MUT_DST));
	}
}
