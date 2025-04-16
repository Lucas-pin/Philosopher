/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   table.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpin <lpin@student.42malaga.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 23:35:05 by lpin              #+#    #+#             */
/*   Updated: 2025/04/16 21:41:15 by lpin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philo.h"

void	create_table(t_table **table)
{
	size_t	memory_size;

	memory_size = sizeof(t_table);
	*table = (t_table *) ft_allocate(memory_size, table);
}

void	init_table(int argc, char **argv, t_table **table)
{
	int		i;

	i = -1;
	while (argv[++i])
	{
		if (i == 0)
			(*table)->philo_num = (int)ft_atoi(argv[i]);
		else if (i == 1)
			(*table)->time_to_die = (uint64_t)ft_atoi(argv[i]);
		else if (i == 2)
			(*table)->time_to_eat = (uint64_t)ft_atoi(argv[i]);
		else if (i == 3)
			(*table)->time_to_sleep = (uint64_t)ft_atoi(argv[i]);
	}
	if (argc == 6)
		(*table)->meals = (int)ft_atoi(argv[4]);
	else
		(*table)->meals = -1;
}
