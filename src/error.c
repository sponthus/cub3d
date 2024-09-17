/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sponthus <sponthus@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 17:00:33 by sponthus          #+#    #+#             */
/*   Updated: 2024/09/17 11:54:58 by sponthus         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

int	write_error(char *error, char *target, int errno)
{
	write(2, "Error\n", 6);
	if (error)
	{
		write(2, error, ft_strlen(error));
		if (target)
		{
			write(2, " : ", 3);
			write(2, target, ft_strlen(target));
		}
	}
	write(2, "\n", 1);
	return (errno);
}
