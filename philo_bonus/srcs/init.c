/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cauvray <cauvray@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 23:03:06 by cauvray           #+#    #+#             */
/*   Updated: 2025/06/27 04:47:25 by cauvray          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

t_args	*init_args(int argc, char *argv[])
{
	t_args	*args ;

	args = malloc(sizeof(t_args));
	args->nb_philo = atol(argv[1]);
	args->time_to_die = atol(argv[2]);
	args->time_to_eat = atol(argv[3]);
	args->time_to_sleep = atol(argv[4]);
	if (argc == 6)
		args->nb_time_must_eat = atol(argv[5]);
	else
		args->nb_time_must_eat = -1 ;
	return (args);
}

t_dinner	*init_dinner(t_args *args)
{
	t_dinner	*dinner ;

	dinner = malloc(sizeof(t_dinner));
	(sem_unlink(SEM_FORK), sem_unlink(SEM_DEATH));
	(sem_unlink(SEM_DISPLAY), sem_unlink(SEM_UPDATE));
	dinner->forks = sem_open(SEM_FORK, O_CREAT, O_RDWR, args->nb_philo);
	dinner->death = sem_open(SEM_DEATH, O_CREAT, O_RDWR, 1);
	dinner->display = sem_open(SEM_DISPLAY, O_CREAT, O_RDWR, 1);
	dinner->update = sem_open(SEM_UPDATE, O_CREAT, O_RDWR, 1);
	if (dinner->forks == SEM_FAILED
		|| dinner->death == SEM_FAILED
		|| dinner->display == SEM_FAILED
		|| dinner->update == SEM_FAILED)
	{
		free_dinner(dinner);
		write(2, "sem_open failed\n", 17);
		return (NULL);
	}
	dinner->lunch_start = get_time_in_ms();
	return (dinner);
}

static t_philo	*init_philo(t_args *args, t_dinner *dinner, int id)
{
	t_philo	*philo ;

	philo = malloc(sizeof(t_philo));
	philo->args = args ;
	philo->dinner = dinner ;
	philo->id = id ;
	philo->nb_time_ate = 0 ;
	philo->last_meal = get_time_in_ms();
	return (philo);
}

t_philo	**create_philos(t_args *args, t_dinner *dinner)
{
	t_philo	**philos ;
	int		i ;

	philos = malloc(sizeof(t_philo *) * args->nb_philo);
	i = -1 ;
	while (++i < args->nb_philo)
	{
		philos[i] = init_philo(args, dinner, i + 1);
		if (!philos[i])
			return (free_philos(philos, i + 1), NULL);
	}
	return (philos);
}
