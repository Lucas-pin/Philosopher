/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpin <lpin@student.42malaga.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 20:47:27 by lpin              #+#    #+#             */
/*   Updated: 2025/04/12 19:15:44 by lpin             ###   ########.fr       */
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
	int				meals;
	uint64_t		start_time;
	uint64_t		time_to_eat;
	uint64_t		time_to_sleep;
	pthread_t		philo_thread;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	t_table			*table;
	pthread_mutex_t philo_mutex;
	uint64_t		last_meal_time;  // Tiempo de la última comida en milisegundos
	int				start_simulation;
}					t_philo;

typedef struct s_table
{
	int				philo_num;
	uint64_t		time_to_die;     // Tiempo de muerte en milisegundos
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

/*---------------------philo-----------------*/
//int		main(int argc, char **argv);

/*---------------------philo_utils-----------------*/
int			ft_isdigit(int c);
long		ft_atoi(char *s);
void		ft_error(enum e_error error, t_table **table);
void		ft_destroy_table(t_table **table);
uint64_t	get_current_time(void);
void		ft_putnbr(uint64_t n);

/*---------------------orchestor-----------------*/
void		ft_entry_orchestor(char **argv);
void		ft_philos_orchestor(int argc, char **argv, t_table **table);

/*---------------------check_entry-----------------*/
void		ft_invalid_entry(char **argv);
void		ft_invalid_number(char **argv);
/*---------------------init-----------------*/
void		ft_create_init_table(int argc, char **argv, t_table **table);
void		ft_create_init_mutex(t_table **table);
void		ft_create_philos(t_table **table);
void		ft_init_philos(t_table **table);
void		ft_create_pthreads(t_table **table);
void		ft_create_monitor(t_table **table);

/*---------------------philo_routine-----------------*/
void		ft_take_fork(t_philo *philo);
void		ft_eat(t_philo *philo);
void		ft_sleep(t_philo *philo);
void		ft_think(t_philo *philo);
void		*ft_philos_routine(void *philo);

/*---------------------monitor_routine-----------------*/
void		*ft_monitor_routine(void *table);

/*---------------------pthread_utils-----------------*/
int			ft_get(pthread_mutex_t *mutex, int *var);
uint64_t	ft_set(pthread_mutex_t *mutex, uint64_t *var, uint64_t new_value);
void		ft_print(t_philo *philo, enum e_philo_status status);
void		lock_fork(pthread_mutex_t *fork, t_philo *philo);
void		take_fork_in_order(pthread_mutex_t *first_fork,
				pthread_mutex_t *second_fork, t_philo *philo);

/*---------------------sincronization-----------------*/
void		wait_for_start(t_philo *philo);
void		alternate_start_delay(t_philo *philo);
bool		is_simulation_stopped(t_philo *philo);
void		wait_to_die(t_philo *philo);

#endif