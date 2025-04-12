/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sincronization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpin <lpin@student.42malaga.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 16:31:31 by lpin              #+#    #+#             */
/*   Updated: 2025/04/12 19:15:11 by lpin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philo.h"

void	wait_for_start(t_philo *philo)
{
	while (!ft_get(&philo->philo_mutex, &philo->start_simulation))
		usleep(100);
}

void	alternate_start_delay(t_philo *philo)
{
	uint64_t	start_time;
	uint64_t	wait_time;

	if (philo->id % 2 != 0)
	{
		start_time = get_current_time();
		wait_time = philo->table->time_to_eat / 2;
		while (get_current_time() - start_time < wait_time)
			usleep(100);
	}
}

bool	is_simulation_stopped(t_philo *philo)
{
	if (ft_get(&philo->table->monitor_mutex, &philo->table->stop_simulation))
		return (true);
	return (false);
}

void	wait_to_die(t_philo *philo)
{
	uint64_t	start_time;
	uint64_t	wait_time;

	start_time = get_current_time();
	wait_time = philo->table->time_to_die;
	while (get_current_time() - start_time < wait_time)
		usleep(100);
}
