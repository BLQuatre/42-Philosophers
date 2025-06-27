/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cauvray <cauvray@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 23:03:06 by cauvray           #+#    #+#             */
/*   Updated: 2025/06/27 03:45:22 by cauvray          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	free_all(t_philo *philo)
{
	sem_close(philo->sem);
	sem_close(philo->sem_eat);
	sem_close(philo->sem_death);
	sem_close(philo->sem_refresh);
	sem_close(philo->sem_print);
	free(philo->ids);
	free(philo->info);
	free(philo);
}

int	main(int ac, char **av)
{
	t_philo		*philo;

	if (ac < 5 || ac > 6)
		return (1);
	philo = malloc(sizeof(t_philo));
	if (!philo)
		return (1);
	if (!check_args(&av[1], ac, philo))
	{
		printf("Invalid input\n");
		return (free(philo), 1);
	}
	if (!init_dinner(philo))
		return (free(philo), 1);
	init_philosophers(philo);
	free_all(philo);
}
