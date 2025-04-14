/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpin <lpin@student.42malaga.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 19:00:33 by lpin              #+#    #+#             */
/*   Updated: 2025/04/13 21:31:44 by lpin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philo.h"

void	create_philos(t_table **table)
{
	int		philo_qty;
	size_t	memory_size;

	philo_qty = (*table)->philo_num;
	memory_size = sizeof(t_philo) * philo_qty;
	(*table)->philos = (t_philo *) ft_allocate(memory_size, table);
}

void	init_philos(t_table **table)
{
	int			i;

	i = 0;
	while (i < (*table)->philo_num)
	{
		(*table)->philos[i].id = i + 1;
		(*table)->philos[i].philo_num = (*table)->philo_num;
		(*table)->philos[i].time_to_eat = (*table)->time_to_eat;
		(*table)->philos[i].time_to_sleep = (*table)->time_to_sleep;
		(*table)->philos[i].meals = (*table)->meals;
		(*table)->philos[i].left_fork = &(*table)->forks[i];
		(*table)->philos[i].right_fork = &(*table)->forks[(i + 1)
			% (*table)->philo_num];
		(*table)->philos[i].table = (*table);
		(*table)->philos[i].start_time = 0;
		(*table)->philos[i].last_meal_time = 0;
		i++;
	}
}
