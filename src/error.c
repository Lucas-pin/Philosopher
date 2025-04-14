/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpin <lpin@student.42malaga.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 20:25:32 by lpin              #+#    #+#             */
/*   Updated: 2025/04/13 20:25:59 by lpin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philo.h"

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
