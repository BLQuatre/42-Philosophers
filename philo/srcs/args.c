/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cauvray <cauvray@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 23:03:06 by cauvray           #+#    #+#             */
/*   Updated: 2025/06/26 23:28:09 by cauvray          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/***
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

static int	args_check(int *tmp_args, int argc)
{
	int	i;

	i = 0;
	while (i < argc)
	{
		if (tmp_args[i] <= 0)
		{
			free(tmp_args);
			return (printf(ERR_ARG_INT), false);
		}
		i++;
	}
	return (true);
}

static bool	args_fill(t_dinner *dinner, int *tmp_args, int argc)
{
	dinner->nb_philo = tmp_args[0];
	dinner->die_time = (long long)(tmp_args[1]);
	dinner->eat_time = (long long)(tmp_args[2]);
	dinner->sleep_time = (long long)(tmp_args[3]);
	dinner->nb_meals = -1;
	if (argc == 5)
		dinner->nb_meals = tmp_args[4];
	free(tmp_args);
	return (true);
}

static bool	args_get(t_dinner *dinner, int argc, char **arg)
{
	int		*tmp_args;
	int		i;

	tmp_args = malloc(sizeof(int) * (argc));
	if (!tmp_args)
		return (printf(ERR_MEMORY), false);
	i = 0;
	while (arg[++i])
		tmp_args[i - 1] = atopi(arg[i]);
	if (!args_check(tmp_args, argc))
		return (false);
	return (args_fill(dinner, tmp_args, argc));
}

int	args_parse(t_dinner *dinner, int argc, char **args)
{
	if (argc != 4 && argc != 5)
		return (printf(ERR_NB_ARG), false);
	return (args_get(dinner, argc, args));
}
