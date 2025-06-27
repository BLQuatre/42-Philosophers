/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cauvray <cauvray@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 23:03:06 by cauvray           #+#    #+#             */
/*   Updated: 2025/06/26 23:28:02 by cauvray          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include <pthread.h>

typedef struct s_philo
{
	int				id;
	int				forks[2];
	int				nb_meals;
	long long		birth;
	long long		last_meal;
	struct s_dinner	*dinner;
	pthread_t		thread;
}	t_philo;

typedef struct s_dinner
{
	int				nb_philo;
	int				nb_meals;
	bool			death_flag;
	long long		eat_time;
	long long		die_time;
	long long		sleep_time;
	pthread_mutex_t	*forks;
	pthread_mutex_t	lock_eat;
	pthread_mutex_t	lock_death;
	pthread_mutex_t	lock_write;
	pthread_t		monitor;
	t_philo			*philo;
}	t_dinner;

#endif
