/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cauvray <cauvray@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 23:03:06 by cauvray           #+#    #+#             */
/*   Updated: 2025/06/26 23:28:42 by cauvray          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	get_time(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) == -1)
		return (printf(ERR_TIME), 0);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	finish_dinner(t_dinner *dinner)
{
	int	i;

	i = 0;
	unlock_mutex(dinner);
	while (i < dinner->nb_philo)
	{
		pthread_mutex_destroy(&dinner->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&dinner->lock_eat);
	pthread_mutex_destroy(&dinner->lock_death);
	pthread_mutex_destroy(&dinner->lock_write);
	free(dinner->forks);
	free(dinner->philo);
}

void	log_action(t_philo *philo, char *msg)
{
	long long	time;

	pthread_mutex_lock(&philo->dinner->lock_write);
	time = get_time() - philo->birth;
	if (!valid_action(philo, 0))
		printf("%lld %d %s\n", time, philo->id, msg);
	pthread_mutex_unlock(&philo->dinner->lock_write);
}

void	smart_sleep(long long time, t_dinner *dinner)
{
	long long	birth;
	long long	last_meal;

	birth = get_time();
	while (!valid_action(dinner->philo, 0))
	{
		last_meal = get_time();
		if (last_meal - birth >= time)
			return ;
		usleep(100);
	}
}

void	crash(char *msg, t_dinner *dinner)
{
	if (msg)
		printf("%s\n", msg);
	if (dinner)
		destroy_mutex(dinner->forks, dinner->nb_philo);
}
