/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpin <lpin@student.42malaga.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 19:54:27 by lpin              #+#    #+#             */
/*   Updated: 2025/04/13 20:53:38 by lpin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philo.h"

void	*ft_allocate(size_t size, t_table **table)
{
	void	*memory;

	memory = malloc(size);
	if (!memory)
		ft_error(ERR_MEMORY_ALLOCATION, table);
	memset(memory, 0, size);
	return (memory);
}

void	ft_destroy_table(t_table **table)
{
	if (table && *table)
	{
		if ((*table)->forks)
		{
			while ((*table)->philo_num > 0)
			{
				pthread_mutex_destroy(
					&(*table)->forks[(*table)->philo_num - 1]);
				(*table)->philo_num--;
			}
			free((*table)->forks);
		}
		pthread_mutex_destroy(&(*table)->monitor_mutex);
		if ((*table)->philos)
			free((*table)->philos);
		free(*table);
		*table = NULL;
	}
}
