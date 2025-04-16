/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpin <lpin@student.42malaga.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 19:11:52 by lpin              #+#    #+#             */
/*   Updated: 2025/04/16 21:41:59 by lpin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philo.h"

void	create_mutex(t_table **table)
{
	int		philo_qty;
	size_t	memory_size;

	philo_qty = (*table)->philo_num;
	memory_size = sizeof(pthread_mutex_t) * philo_qty;
	(*table)->forks = (pthread_mutex_t *) ft_allocate(memory_size, table);
}

void	init_mutex(t_table **table)
{
	int				i;
	pthread_mutex_t	*current_fork;
	pthread_mutex_t	*current_philo;

	i = -1;
	if (pthread_mutex_init(&(*table)->monitor_mutex, NULL) != 0
		|| pthread_mutex_init(&(*table)->global_mutex, NULL) != 0)
		ft_error(ERR_MUTEX_INIT, table);
	while (++i < (*table)->philo_num)
	{
		current_fork = &(*table)->forks[i];
		current_philo = &(*table)->philos[i].philo_mutex;
		if (pthread_mutex_init(current_fork, NULL) != 0
			|| pthread_mutex_init(current_philo, NULL) != 0)
		{
			while (--i > 0)
			{
				current_fork = &(*table)->forks[i];
				current_philo = &(*table)->philos[i].philo_mutex;
				pthread_mutex_destroy(current_fork);
				pthread_mutex_destroy(current_philo);
			}
			ft_error(ERR_MUTEX_INIT, table);
		}
	}
}
