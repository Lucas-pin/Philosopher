/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpin <lpin@student.42malaga.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 23:47:29 by lpin              #+#    #+#             */
/*   Updated: 2025/04/16 21:41:28 by lpin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philo.h"

static void	ft_eat(t_philo *philo)
{
	long	start_eat;

	if (is_simulation_stopped(philo))
		return ;
	ft_print(philo, PHILO_EATING);
	start_eat = get_current_time();
	while (get_current_time() - start_eat < philo->time_to_eat)
		usleep(100);
	if (philo->meals > 0)
		philo->meals--;
	ft_set(&philo->philo_mutex, &philo->last_meal_time, get_current_time());
}

static void	ft_take_fork(t_philo *philo)
{
	if (philo->right_fork == philo->left_fork)
	{
		lock_fork(philo->left_fork, philo);
		wait_to_die(philo);
	}
	else if (philo->id % 2)
		take_fork_in_order(philo->left_fork, philo->right_fork, philo);
	else
		take_fork_in_order(philo->right_fork, philo->left_fork, philo);
	ft_eat(philo);
	if (philo->right_fork == philo->left_fork)
		pthread_mutex_unlock(philo->left_fork);
	else
	{
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
	}
}

static void	ft_sleep(t_philo *philo)
{
	long	start_sleep;

	if (is_simulation_stopped(philo))
		return ;
	ft_print(philo, PHILO_SLEEPING);
	start_sleep = get_current_time();
	while (get_current_time() - start_sleep < philo->time_to_sleep)
		usleep(100);
}

static void	ft_think(t_philo *philo)
{
	if (is_simulation_stopped(philo))
		return ;
	ft_print(philo, PHILO_THINKING);
}

void	*ft_philos_routine(void *philo)
{
	t_philo	*philo_ptr;

	philo_ptr = (t_philo *)philo;
	wait_for_start(philo_ptr);
	simetric_start_delay(philo_ptr);
	while ((is_simulation_stopped(philo)) == false && philo_ptr->meals != 0)
	{
		ft_take_fork(philo_ptr);
		ft_sleep(philo_ptr);
		ft_think(philo_ptr);
		if (philo_ptr->meals == 0)
			pthread_exit(NULL);
	}
	return (NULL);
}
