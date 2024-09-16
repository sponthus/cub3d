/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sponthus <sponthus@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 17:00:33 by sponthus          #+#    #+#             */
/*   Updated: 2024/09/16 12:56:32 by sponthus         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	write_error(char *error, char *target)
{
	(void)!write(2, "Error\n", 6);
	if (error)
	{
		(void)!write(2, error, ft_strlen(error));
		if (target)
			(void)!write(2, target, ft_strlen(target));
	}
	(void)!write(2, "\n", 1);
}
