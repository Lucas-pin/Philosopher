/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   orchestor.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpin <lpin@student.42malaga.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 19:47:54 by lpin              #+#    #+#             */
/*   Updated: 2025/04/12 16:30:15 by lpin             ###   ########.fr       */
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
	ft_create_init_table(argc, argv, table);
	ft_create_init_mutex(table);
	ft_create_philos(table);
	ft_init_philos(table);
	ft_create_pthreads(table);
	ft_create_monitor(table);
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
