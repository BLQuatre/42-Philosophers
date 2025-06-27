/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cauvray <cauvray@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 23:03:06 by cauvray           #+#    #+#             */
/*   Updated: 2025/06/27 04:47:25 by cauvray          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	delete_semaphores(t_dinner *dinner)
{
	(sem_close(dinner->forks), sem_unlink(SEM_FORK));
	(sem_close(dinner->death), sem_unlink(SEM_DEATH));
	(sem_close(dinner->display), sem_unlink(SEM_DISPLAY));
	(sem_close(dinner->update), sem_unlink(SEM_UPDATE));
}

void	free_dinner(t_dinner *dinner)
{
	delete_semaphores(dinner);
	free(dinner);
}

void	free_philos(t_philo **philosophers, int nb_philos)
{
	while (nb_philos--)
		free(philosophers[nb_philos]);
	free(philosophers);
}

void	free_all(t_philo **philos, t_dinner *dinner, t_args *args)
{
	free_philos(philos, args->nb_philo);
	free_dinner(dinner);
	free(args);
}
