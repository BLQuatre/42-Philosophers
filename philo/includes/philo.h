/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cauvray <cauvray@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 23:03:06 by cauvray           #+#    #+#             */
/*   Updated: 2025/06/26 23:27:58 by cauvray          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <stdbool.h>
# include <sys/time.h>
# include <unistd.h>
# include <limits.h>

# include "structs.h"
# include "messages.h"

# define MIN_PHILO 1
# define MAX_PHILO INT_MAX

int			args_parse(t_dinner *dinner, int argc, char **args);
bool		init_dinner(t_dinner *dinner);
void		*monitor(void *arg);
void		destroy_mutex(pthread_mutex_t *mtx, int max);
void		unlock_mutex(t_dinner *dinner);
bool		start_dinner(t_dinner *dinner);
bool		valid_action(t_philo *philo, bool condition);
long long	get_time(void);
void		crash(char *msg, t_dinner *dinner);
void		log_action(t_philo *philo, char *msg);
void		smart_sleep(long long time, t_dinner *dinner);
void		finish_dinner(t_dinner *dinner);
void		action_sleep(t_philo *philo);
void		action_think(t_philo *philo);
bool		action_eat(t_philo *philo);

#endif
