/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pthreads.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpin <lpin@student.42malaga.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 19:57:36 by lpin              #+#    #+#             */
/*   Updated: 2025/04/16 21:41:43 by lpin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philo.h"

static void	create_thread(pthread_t *thread, void *(*routine)(void *),
	void *routine_arg, t_table **table)
{
	if (pthread_create(thread, NULL, routine, routine_arg) != 0)
		ft_error(ERR_THREAD_CREATE, table);
}

void	create_philos_threads(t_table **table)
{
	int			i;
	t_philo		*current_philo;

	i = 0;
	while (i < (*table)->philo_num)
	{
		current_philo = &(*table)->philos[i];
		create_thread(&(*table)->philos[i].philo_thread,
			ft_philos_routine, (void *) current_philo, table);
		i++;
	}
}

void	create_monitor_thread(t_table **table)
{
	create_thread(&(*table)->monitor_thread,
		ft_monitor_routine, (void *) *table, table);
}
