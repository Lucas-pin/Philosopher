/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpin <lpin@student.42malaga.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 23:35:05 by lpin              #+#    #+#             */
/*   Updated: 2025/04/12 18:20:34 by lpin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philo.h"

void	ft_create_init_table(int argc, char **argv, t_table **table)
{
	int		i;

	i = -1;
	*table = malloc(sizeof(t_table));
	if (!*table)
		ft_error(ERR_MEMORY_ALLOCATION, table);
	memset(*table, 0, sizeof(t_table));
	while (argv[++i])
	{
		if (i == 0)
			(*table)->philo_num = (int)ft_atoi(argv[i]);
		else if (i == 1)
			(*table)->time_to_die = (uint64_t)ft_atoi(argv[i]);
		else if (i == 2)
			(*table)->time_to_eat = (uint64_t)ft_atoi(argv[i]);
		else if (i == 3)
			(*table)->time_to_sleep = (uint64_t)ft_atoi(argv[i]);
	}
	if (argc == 6)
		(*table)->meals = (int)ft_atoi(argv[4]);
	else
		(*table)->meals = -1;
	if (pthread_mutex_init(&(*table)->monitor_mutex, NULL) != 0
		|| pthread_mutex_init(&(*table)->global_mutex, NULL) != 0)
		ft_error(ERR_MUTEX_INIT, table);
}

void	ft_create_init_mutex(t_table **table)
{
	int	i;

	i = 0;
	(*table)->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t)
			* (*table)->philo_num);
	if (!(*table)->forks)
		ft_error(ERR_MEMORY_ALLOCATION, table);
	while (i < (*table)->philo_num)
	{
		if (pthread_mutex_init(&(*table)->forks[i], NULL) != 0)
		{
			while (i > 0)
			{
				pthread_mutex_destroy(&(*table)->forks[i]);
				i--;
			}
			ft_error(ERR_MUTEX_INIT, table);
			break ;
		}
		i++;
	}
}

void	ft_create_philos(t_table **table)
{
	(*table)->philos = (t_philo *)malloc(sizeof(t_philo) * (*table)->philo_num);
	if (!(*table)->philos)
		ft_error(ERR_MEMORY_ALLOCATION, table);
	memset((*table)->philos, 0, sizeof(t_philo) * (*table)->philo_num);
}

void	ft_init_philos(t_table **table)
{
	int			i;

	i = 0;
	while (i < (*table)->philo_num)
	{
		(*table)->philos[i].id = i + 1;
		(*table)->philos[i].time_to_eat = (*table)->time_to_eat;
		(*table)->philos[i].time_to_sleep = (*table)->time_to_sleep;
		(*table)->philos[i].meals = (*table)->meals;
		(*table)->philos[i].left_fork = &(*table)->forks[i];
		(*table)->philos[i].right_fork = &(*table)->forks[(i + 1)
			% (*table)->philo_num];
		(*table)->philos[i].table = (*table);
		if (pthread_mutex_init(&(*table)->philos[i].philo_mutex, NULL) != 0)
			ft_error(ERR_MUTEX_INIT, table);
		(*table)->philos[i].start_time = 0;
		(*table)->philos[i].last_meal_time = 0;
		i++;
	}
}

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

void	ft_create_monitor(t_table **table)
{
	pthread_t	monitor_thread;

	if (pthread_create(&(*table)->monitor_thread, NULL,
			ft_monitor_routine, *table) != 0)
		ft_error(ERR_THREAD_CREATE, table);
}
