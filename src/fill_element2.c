/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_element2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sponthus <sponthus@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 14:41:52 by sponthus          #+#    #+#             */
/*   Updated: 2024/09/16 14:43:47 by sponthus         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	fill_colors(t_pars *pars, t_list *actual)
{
	if (ft_strncmp(actual->id, "F", 1) == 0)
	{
		if (pars->floor_color == NULL)
		{
			pars->floor_color = actual->content;
			printf("Valid floor element registered %s\n", actual->content);
		}
		else
		 	return (write_error("F color redefined : ", actual->content), 1);
	}
	if (ft_strncmp(actual->id, "C", 1) == 0)
	{
		if (pars->ceiling_color == NULL)
		{
			pars->ceiling_color = actual->content;
			printf("Valid ceiling element registered %s\n", actual->content);
		}
		else
		 	return (write_error("C color redefined : ", actual->content), 1);
	}
	return (0);
}
