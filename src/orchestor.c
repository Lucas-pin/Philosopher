/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   orchestor.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpin <lpin@student.42malaga.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 19:47:54 by lpin              #+#    #+#             */
/*   Updated: 2025/04/13 21:12:44 by lpin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philo.h"

void	ft_entry_orchestor(char **argv)
{
	ft_invalid_entry(argv);
	ft_invalid_number(argv);
}

void	ft_philos_orchestor(int argc, char **argv, t_table **table)
{
	int	i;

	i = 0;
	create_table(table);
	init_table(argc, argv, table);
	create_mutex(table);
	create_philos(table);
	init_mutex(table);
	init_philos(table);
	start_simulation(table);
	create_philos_threads(table);
	create_monitor_thread(table);
	while (i < (*table)->philo_num)
	{
		pthread_join((*table)->philos[i].philo_thread, NULL);
		i++;
	}
	ft_set(&(*table)->monitor_mutex,
		(uint64_t *)&(*table)->stop_simulation, 1);
	pthread_join((*table)->monitor_thread, NULL);
	ft_destroy_table(table);
}
