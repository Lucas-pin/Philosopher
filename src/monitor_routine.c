/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_routine.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpin <lpin@student.42malaga.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 17:58:34 by lpin              #+#    #+#             */
/*   Updated: 2025/04/16 21:34:20 by lpin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philo.h"

static int	ft_check_meals_time(t_table *table_ptr, int index)
{
	if ((get_current_time() - table_ptr->philos[index].last_meal_time)
		> table_ptr->time_to_die)
	{
		ft_print(&(table_ptr->philos[index]), PHILO_DEAD);
		ft_set(&table_ptr->monitor_mutex,
			(uint64_t *)&table_ptr->stop_simulation, 1);
		return (1);
	}
	return (0);
}

static int	ft_check_simulation(t_table *table_ptr)
{
	if (ft_get(&table_ptr->monitor_mutex,
			&table_ptr->stop_simulation) == 1)
		return (1);
	return (0);
}

void	*ft_monitor_routine(void *table)
{
	t_table		*table_ptr;
	int			i;

	table_ptr = (t_table *)table;
	while (1)
	{
		i = 0;
		while (i < table_ptr->philo_num)
		{
			pthread_mutex_lock(&table_ptr->philos[i].philo_mutex);
			if (ft_check_meals_time(table_ptr, i) == 1
				|| ft_check_simulation(table_ptr) == 1)
			{
				pthread_mutex_unlock(&table_ptr->philos[i].philo_mutex);
				return (NULL);
			}
			pthread_mutex_unlock(&table_ptr->philos[i].philo_mutex);
			i++;
		}
	}
	return (NULL);
}
