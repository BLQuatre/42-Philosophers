/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cauvray <cauvray@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 23:03:06 by cauvray           #+#    #+#             */
/*   Updated: 2025/06/26 23:28:37 by cauvray          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_dinner	dinner;

	if (!args_parse(&dinner, ac - 1, av))
		return (EXIT_FAILURE);
	if (!init_dinner(&dinner))
		return (EXIT_FAILURE);
	if (!start_dinner(&dinner))
		return (EXIT_FAILURE);
	finish_dinner(&dinner);
	return (EXIT_SUCCESS);
}
