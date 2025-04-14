/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpin <lpin@student.42malaga.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 20:47:27 by lpin              #+#    #+#             */
/*   Updated: 2025/04/13 21:30:44 by lpin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <stdlib.h>
# include <sys/time.h>
# include <stdint.h>  // Incluir stdint.h para uint64_t
# include <string.h>
# include <stdbool.h>

// Prototipo de las estructuras
typedef struct s_table	t_table;
typedef struct s_philo	t_philo;

// Enumeración de errores
enum e_error
{
	ERR_INVALID_ARGUMENTS,
	ERR_MEMORY_ALLOCATION,
	ERR_MUTEX_INIT,
	ERR_THREAD_CREATE,
	ERR_THREAD_JOIN
};

enum e_philo_status
{
	PHILO_TAKE_FORK,
	PHILO_EATING,
	PHILO_SLEEPING,
	PHILO_THINKING,
	PHILO_DEAD,
	PHILO_TAKE_LEFT_FORK,
};

typedef struct s_philo
{
	int				id;
	int				philo_num;
	int				meals;
	uint64_t		start_time;
	uint64_t		time_to_eat;
	uint64_t		time_to_sleep;
	pthread_t		philo_thread;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	t_table			*table;
	pthread_mutex_t	philo_mutex;
	uint64_t		last_meal_time;
	int				start_simulation;
}					t_philo;

typedef struct s_table
{
	int				philo_num;
	uint64_t		time_to_die;
	uint64_t		time_to_eat;
	uint64_t		time_to_sleep;
	int				meals;
	t_philo			*philos;
	pthread_mutex_t	*forks;
	pthread_t		monitor_thread;
	pthread_mutex_t	monitor_mutex;
	pthread_mutex_t	global_mutex;
	int				stop_simulation;
}					t_table;

/*---------------------philo---------------------------*/
//int		main(int argc, char **argv);

/*---------------------check_entry---------------------*/
void		ft_invalid_entry(char **argv);
void		ft_invalid_number(char **argv);

/*---------------------error---------------------------*/
void		ft_error(enum e_error error, t_table **table);

/*--------------------memory_utils---------------------*/
void		*ft_allocate(size_t size, t_table **table);
void		ft_destroy_table(t_table **table);

/*---------------------monitor_routine-----------------*/
void		*ft_monitor_routine(void *table);

/*--------------------------mutex----------------------*/
void		create_mutex(t_table **table);
void		init_mutex(t_table **table);

/*---------------------orchestor-----------------------*/
void		ft_entry_orchestor(char **argv);
void		ft_philos_orchestor(int argc, char **argv, t_table **table);

/*---------------------philo_routine-------------------*/
void		*ft_philos_routine(void *philo);

/*-------------------------philos----------------------*/
void		create_philos(t_table **table);
void		init_philos(t_table **table);

/*-------------------phthread_utils--------------------*/
int			ft_get(pthread_mutex_t *mutex, int *var);
uint64_t	ft_set(pthread_mutex_t *mutex, uint64_t *var, uint64_t new_value);
void		ft_print(t_philo *philo, enum e_philo_status status);
void		lock_fork(pthread_mutex_t *fork, t_philo *philo);
void		take_fork_in_order(pthread_mutex_t *first_fork,
				pthread_mutex_t *second_fork, t_philo *philo);

/*--------------------pthreads.c-----------------------*/
void		create_philos_threads(t_table **table);
void		create_monitor_thread(t_table **table);

/*------------------sincronization---------------------*/
void		start_simulation(t_table **table);
void		wait_for_start(t_philo *philo);
void		simetric_start_delay(t_philo *philo);
void		asimetric_start_delay(t_philo *philo);
bool		is_simulation_stopped(t_philo *philo);
void		wait_to_die(t_philo *philo);

/*----------------------table-------------------------*/
void		create_table(t_table **table);
void		init_table(int argc, char **argv, t_table **table);

/*---------------------utils----------------------------*/
int			ft_isdigit(int c);
long		ft_atoi(char *s);
uint64_t	get_current_time(void);

#endif