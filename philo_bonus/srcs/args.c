/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cauvray <cauvray@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 23:03:06 by cauvray           #+#    #+#             */
/*   Updated: 2025/06/27 03:51:57 by cauvray          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static int	is_num(char **av)
{
	int	i;
	int	j;

	j = 0;
	i = -1;
	while (av[++i])
	{
		j = -1;
		while (av[i][++j])
		{
			if (!(av[i][j] >= '0' && av[i][j] <= '9'))
				return (0);
		}
	}
	return (1);
}

/**
 * @brief Converts a string to an integer.
 * atopi = ascii to positive integer
 * @param str The string to convert.
 * @return The converted integer, or -1 if the conversion fails.
 */
static int	atopi(char *str)
{
	long long	nb;

	nb = 0;
	while (*str)
	{
		if (*str < '0' || *str > '9')
			return (-1);
		nb = (nb * 10) + (*str++ - '0');
	}
	if (nb < MIN_PHILO || nb > MAX_PHILO)
		return (-1);
	return ((int) nb);
}

int	check_args(char **av, int ac, t_philo *philo)
{
	int		i;
	long	*args;

	if (!is_num(av))
		return (0);
	args = malloc(sizeof(long) * 5);
	if (!args)
		return (0);
	i = -1;
	while (av[++i])
		args[i] = atopi(av[i]);
	if (ac == 5)
		args[4] = 0;
	i = -1;
	while (av[++i])
	{
		if (args[i] <= 0 || args[i] > INT_MAX || args[i] < INT_MIN)
			return (free(args), 0);
	}
	philo->info = args;
	return (1);
}
