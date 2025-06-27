/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cauvray <cauvray@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 23:03:06 by cauvray           #+#    #+#             */
/*   Updated: 2025/06/27 04:48:26 by cauvray          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

long	ft_atol(const char *nptr)
{
	long	res ;
	int		sign ;

	res = 0 ;
	sign = 1 ;
	while ((*nptr >= 9 && *nptr <= 13) || *nptr == ' ')
		nptr++ ;
	if (*nptr == '+' || *nptr == '-')
		if (*nptr++ == '-')
			sign = -1 ;
	while (*nptr >= '0' && *nptr <= '9')
		res = res * 10 + (*(nptr++) - '0');
	return (res * sign);
}
