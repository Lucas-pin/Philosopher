/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_entry.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpin <lpin@student.42malaga.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 19:54:15 by lpin              #+#    #+#             */
/*   Updated: 2025/04/06 22:01:00 by lpin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philo.h"

void	ft_invalid_entry(char **argv)
{
	char	*temp;

	while (*argv)
	{
		temp = *argv;
		while (*temp)
		{
			if (!ft_isdigit(*temp) && *temp != ' ')
				ft_error(ERR_INVALID_ARGUMENTS, NULL);
			if (ft_isdigit(*temp) == 1 && (*(temp + 1) != ' '
					&& !ft_isdigit(*(temp + 1))
					&& *(temp + 1) != '\0'))
				ft_error(ERR_INVALID_ARGUMENTS, NULL);
			temp++;
		}
		argv++;
	}
}

void	ft_invalid_number(char **argv)
{
	int		i;
	int		num;

	i = 0;
	while (argv[i])
	{
		num = ft_atoi(argv[i]);
		if (num < 0)
			ft_error(ERR_INVALID_ARGUMENTS, NULL);
		i++;
	}
}
