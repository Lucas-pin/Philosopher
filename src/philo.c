/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpin <lpin@student.42malaga.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 20:44:34 by lpin              #+#    #+#             */
/*   Updated: 2025/04/07 09:02:02 by lpin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philo.h"

int	main(int argc, char **argv)
{
	t_table	*table;

	table = NULL;
	if (argc < 5 || argc > 6)
		ft_error(ERR_INVALID_ARGUMENTS, NULL);
	else
	{
		argv++;
		ft_entry_orchestor(argv);
		ft_philos_orchestor(argc, argv, &table);
	}
	return (0);
}