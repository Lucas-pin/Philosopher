/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sincronization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpin <lpin@student.42malaga.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 16:31:31 by lpin              #+#    #+#             */
/*   Updated: 2025/04/13 21:29:50 by lpin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philo.h"

void	start_simulation(t_table **table)
{
	int			i;
	uint64_t	current_time;

	i = 0;
	current_time = get_current_time();
	while (i < (*table)->philo_num)
	{
		ft_set(&(*table)->philos[i].philo_mutex,
			&(*table)->philos[i].start_time, current_time);
		ft_set(&(*table)->philos[i].philo_mutex,
			&(*table)->philos[i].last_meal_time, current_time);
		ft_set(&(*table)->philos[i].philo_mutex,
			(uint64_t *)&(*table)->philos[i].start_simulation, 1);
		i++;
	}
}

void	wait_for_start(t_philo *philo)
{
	while (!ft_get(&philo->philo_mutex, &philo->start_simulation))
		usleep(50);
}

void	simetric_start_delay(t_philo *philo)
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

void	asimetric_start_delay(t_philo *philo)
{
	uint64_t	start_time;
	uint64_t	wait_time;

	start_time = get_current_time();
	wait_time = philo->id * philo->table->time_to_eat / 2;
	while (get_current_time() - start_time < wait_time)
		usleep(100);
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
