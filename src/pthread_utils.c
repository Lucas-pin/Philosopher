/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pthread_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpin <lpin@student.42malaga.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 17:38:44 by lpin              #+#    #+#             */
/*   Updated: 2025/04/12 17:53:08 by lpin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philo.h"

int	ft_get(pthread_mutex_t *mutex, int *var)
{
	int	value;

	pthread_mutex_lock(mutex);
	value = *var;
	pthread_mutex_unlock(mutex);
	return (value);
}

uint64_t	ft_set(pthread_mutex_t *mutex, uint64_t *var, uint64_t new_value)
{
	pthread_mutex_lock(mutex);
	*var = new_value;
	pthread_mutex_unlock(mutex);
}

void	ft_print(t_philo *philo, enum e_philo_status status)
{
	int				id;
	uint64_t		start_time;
	uint64_t		timestamp_in_ms;
	pthread_mutex_t	*mutex;

	id = philo->id;
	start_time = philo->start_time;
	mutex = &philo->table->global_mutex;
	pthread_mutex_lock(mutex);
	timestamp_in_ms = get_current_time() - start_time;
	if (status == PHILO_TAKE_FORK)
		printf("%ld %d %s\n", timestamp_in_ms, id, "has taken a fork");
	else if (status == PHILO_EATING)
		printf("%ld %d %s\n", timestamp_in_ms, id, "is eating");
	else if (status == PHILO_SLEEPING)
		printf("%ld %d %s\n", timestamp_in_ms, id, "is sleeping");
	else if (status == PHILO_THINKING)
		printf("%ld %d %s\n", timestamp_in_ms, id, "is thinking");
	else if (status == PHILO_DEAD)
		printf("%ld %d %s\n", timestamp_in_ms, id, "died");
	pthread_mutex_unlock(mutex);
}

void	lock_fork(pthread_mutex_t *fork, t_philo *philo)
{
	pthread_mutex_lock(fork);
	if (is_simulation_stopped(philo))
	{
		pthread_mutex_unlock(fork);
		pthread_exit(NULL);
	}
	ft_print(philo, PHILO_TAKE_FORK);
}

void	take_fork_in_order(pthread_mutex_t *first_fork,
	pthread_mutex_t *second_fork, t_philo *philo)
{
	lock_fork(first_fork, philo);
	pthread_mutex_lock(second_fork);
	if (is_simulation_stopped(philo))
	{
		pthread_mutex_unlock(first_fork);
		pthread_mutex_unlock(second_fork);
		pthread_exit(NULL);
	}
	ft_print(philo, PHILO_TAKE_FORK);
}
