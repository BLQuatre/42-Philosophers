/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cauvray <cauvray@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 23:03:06 by cauvray           #+#    #+#             */
/*   Updated: 2025/06/27 03:40:42 by cauvray          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <fcntl.h>
# include <pthread.h>
# include <semaphore.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <unistd.h>
# include <limits.h>

# define MIN_PHILO 1
# define MAX_PHILO INT_MAX

typedef struct s_philo
{
	int			i;
	long		*info;
	int			nb_meals;
	int			is_dead;
	long		init_time;
	sem_t		*sem;
	sem_t		*sem_death;
	sem_t		*sem_refresh;
	sem_t		*sem_eat;
	sem_t		*sem_print;
	pthread_t	th;
	int			*ids;
	long		eating_time;
}				t_philo;

int				init_dinner(t_philo *philo);
void			smart_sleep(t_philo *vars, int time);
int				check_args(char **av, int ac, t_philo *philo);
void			init_philosophers(t_philo *ptr);
long			get_time(void);
long			get_time_since(time_t time);

void			action_think(t_philo *arg);
void			take_fork(t_philo *arg);
void			action_eat(t_philo *arg);
void			start_eating(t_philo *arg);

enum
{
	philo_n,
	time_to_die,
	eat_time,
	sleep_time,
	nb_meals
};

#endif
