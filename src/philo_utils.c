/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpin <lpin@student.42malaga.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 20:07:50 by lpin              #+#    #+#             */
/*   Updated: 2025/04/09 20:17:50 by lpin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philo.h"

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

long	ft_atoi(char *s)
{
	long	nbr;
	int		flag;

	nbr = 0;
	flag = 1;
	while (*s && (*s < '0' || *s > '9'))
	{
		if (*s == '-')
			flag = -1;
		s++;
	}
	while (*s && (*s >= '0' && *s <= '9'))
	{
		nbr = nbr * 10 + (*s - '0');
		s++;
	}
	return (nbr * flag);
}

void	ft_putnbr(uint64_t n)
{
	char		mod;
	uint64_t	div;

	div = n / 10;
	mod = (n % 10) + '0';
	if (div != 0)
		ft_putnbr(div);
	if (mod >= '0' && mod <= '9')
		write(1, &mod, 1);
}

void	ft_error(enum e_error error, t_table **table)
{
	if (error == ERR_INVALID_ARGUMENTS)
		printf("Error: Invalid arguments\n");
	else if (error == ERR_MEMORY_ALLOCATION)
		printf("Error: Memory allocation\n");
	else if (error == ERR_MUTEX_INIT)
		printf("Error: Mutex initialization\n");
	else if (error == ERR_THREAD_CREATE)
		printf("Error: Thread creation\n");
	else if (error == ERR_THREAD_JOIN)
		printf("Error: Thread join\n");
	if (table && *table)
		ft_destroy_table(table);
	exit(1);
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
void	ft_ussleep(long mls)
{
	long	start;

	start = get_current_time();
	while (get_current_time() - start < mls)
		usleep(100);
}

uint64_t get_current_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}