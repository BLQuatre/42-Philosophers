/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cauvray <cauvray@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 23:03:06 by cauvray           #+#    #+#             */
/*   Updated: 2025/06/27 04:47:25 by cauvray          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	error_args(void)
{
	write(STDERR_FILENO, "Philo args :\
	\n(uint) number_of_philosophers (strictly positive)\
	\n(uint) time_to_die (strictly positive)\
	\n(uint) time_to_eat (strictly positive)\
	\n(uint) time_to_sleep (strictly positive)\
	\n(uint) [number_of_times_each_philosopher_must_eat] (strictly positive)\
	\n", 260);
}

void	error_fork(t_dinner *dinner)
{
	sem_wait(dinner->display);
	write(STDERR_FILENO, "fork failed\n", 13);
	sem_post(dinner->display);
}

void	error_pthread(t_dinner *dinner)
{
	write(STDERR_FILENO, "Pthread create/join failed\n", 28);
	sem_wait(dinner->update);
	dinner->death->__align = 0 ;
	sem_post(dinner->update);
}
