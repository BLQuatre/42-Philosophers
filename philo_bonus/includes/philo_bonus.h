/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cauvray <cauvray@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 23:03:06 by cauvray           #+#    #+#             */
/*   Updated: 2025/06/27 04:47:25 by cauvray          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <pthread.h>
# include <semaphore.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/time.h>
# include <signal.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <stdbool.h>
# include <limits.h>

# define SEM_FORK		"philo_forks"
# define SEM_DEATH		"philo_death"
# define SEM_DISPLAY	"philo_display"
# define SEM_UPDATE		"philo_update"

typedef struct s_args
{
	int	nb_philo;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	nb_time_must_eat;
}	t_args;

typedef struct s_dinner
{
	sem_t			*forks;
	sem_t			*death; // serves as a shared between processes boolean
	sem_t			*display;
	sem_t			*update;
	long			lunch_start;
}	t_dinner;

typedef struct s_philo
{
	t_args			*args;
	t_dinner			*dinner;
	int				id;
	int				nb_time_ate;
	long			last_meal;
}	t_philo;

void	philosophing(t_philo **philos, int index, t_dinner *dinner, t_args *args);
int		parsing(int argc, char *argv[]);
void	error_args(void);
void	error_fork(t_dinner *dinner);
void	error_pthread(t_dinner *dinner);
t_args	*init_args(int argc, char *argv[]);
t_dinner	*init_dinner(t_args *args);
t_philo	**create_philos(t_args *args, t_dinner *dinner);
void	display_action(t_philo *philo, t_dinner *dinner, char *msg);
void	action_eat(t_philo *philo, t_dinner *dinner);
void	action_sleep_think(t_philo *philo, t_dinner *dinner);
void	free_dinner(t_dinner *dinner);
void	free_philos(t_philo **philosophers, int nb_philos);
void	free_all(t_philo **philos, t_dinner *dinner, t_args *args);
int		ft_isdigit(int c);
long	ft_atol(const char *nptr);
long	get_time_in_ms(void);
long	get_time_since(long time);
void	smart_sleep(long ms);

#endif
