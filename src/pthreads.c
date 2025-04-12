/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pthreads.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpin <lpin@student.42malaga.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 19:57:36 by lpin              #+#    #+#             */
/*   Updated: 2025/04/12 20:00:14 by lpin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philo.h"

void	ft_create_pthreads(t_table **table)
{
	int			i;
	uint64_t	current_time;

	i = 0;
	current_time = get_current_time();
	while (i < (*table)->philo_num)
	{
		if (pthread_create(&(*table)->philos[i].philo_thread, NULL,
				ft_philos_routine, &(*table)->philos[i]) != 0)
			ft_error(ERR_THREAD_CREATE, table);
		i++;
	}
	i = -1;
	while (++i < (*table)->philo_num)
	{
		ft_set(&(*table)->philos[i].philo_mutex,
			&(*table)->philos[i].start_time, current_time);
		ft_set(&(*table)->philos[i].philo_mutex,
			&(*table)->philos[i].last_meal_time, current_time);
		ft_set(&(*table)->philos[i].philo_mutex,
			(uint64_t *)&(*table)->philos[i].start_simulation, 1);
	}
}
