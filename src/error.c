/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: endoliam <endoliam@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 17:00:33 by sponthus          #+#    #+#             */
/*   Updated: 2024/09/11 00:05:21 by endoliam         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	write_error(char *error, char *target)
{
	(void)!write(2, "Error\n", 5);
	if (error)
	{
		(void)!write(2, error, ft_strlen(error));
		if (target)
			(void)!write(2, target, ft_strlen(target));
	}
	(void)!write(2, "\n", 1);
}
