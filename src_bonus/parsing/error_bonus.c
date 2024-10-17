/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sponthus <sponthus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 17:00:33 by sponthus          #+#    #+#             */
/*   Updated: 2024/10/17 11:16:49 by sponthus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils_bonus.h"

int	write_err(char *error, char *target, char *obj, int errno)
{
	write(2, "Error\n", 6);
	if (error)
	{
		write(2, error, ft_strlen(error));
		if (obj)
		{
			write(2, " ", 1);
			write(2, obj, ft_strlen(obj));
		}
		if (target)
		{
			write(2, " : ", 3);
			write(2, target, ft_strlen(target));
		}
	}
	write(2, "\n", 1);
	return (errno);
}
