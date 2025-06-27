/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cauvray <cauvray@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 23:03:06 by cauvray           #+#    #+#             */
/*   Updated: 2025/06/27 04:47:25 by cauvray          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static bool	serving_plates(t_args *args, t_dinner *dinner,
	t_philo **philos, pid_t *pids)
{
	int	i ;

	i = -1 ;
	while (++i < args->nb_philo)
	{
		pids[i] = fork();
		if (pids[i] < 0)
		{
			error_fork(dinner);
			sem_wait(dinner->update);
			dinner->death->__align = 0 ;
			sem_post(dinner->update);
			return (EXIT_FAILURE);
		}
		if (pids[i] == 0)
		{
			free(pids);
			philosophing(philos, i, dinner, args);
		}
		usleep(2);
	}
	return (EXIT_SUCCESS);
}

static void	waiting_til_they_finish(t_args *args, pid_t *pids)
{
	int	i ;

	i = -1 ;
	while (++i < args->nb_philo)
		if (pids[i] != -1)
			waitpid(pids[i], NULL, 0);
}

static bool	bon_appetit(t_args *args, t_dinner *dinner)
{
	t_philo	**philos ;
	pid_t	*pids ;
	bool	status ;

	philos = create_philos(args, dinner);
	if (!philos)
		return (EXIT_FAILURE);
	pids = malloc((args->nb_philo + 1) * sizeof(pid_t));
	memset(pids, -1, (args->nb_philo + 1) * sizeof(pid_t));
	status = serving_plates(args, dinner, philos, pids);
	waiting_til_they_finish(args, pids);
	free(pids);
	free_philos(philos, args->nb_philo);
	return (status);
}

int	main(int argc, char *argv[])
{
	t_args	*args ;
	t_dinner	*dinner ;
	bool	status ;

	if (argc < 5 || argc > 6 || !parsing(argc, argv))
		return (error_args(), EXIT_FAILURE);
	args = init_args(argc, argv);
	dinner = init_dinner(args);
	if (!dinner)
		return (free(args), EXIT_FAILURE);
	status = bon_appetit(args, dinner);
	free(args);
	free_dinner(dinner);
	return (status);
}
