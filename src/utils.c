/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpin <lpin@student.42malaga.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 20:07:50 by lpin              #+#    #+#             */
/*   Updated: 2025/04/13 20:26:02 by lpin             ###   ########.fr       */
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

uint64_t	get_current_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}
