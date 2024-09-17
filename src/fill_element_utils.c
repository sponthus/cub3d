/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_element_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sponthus <sponthus@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 14:29:55 by sponthus          #+#    #+#             */
/*   Updated: 2024/09/17 12:02:24 by sponthus         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	fill_no(t_pars *pars, t_list *actual)
{
	if (ft_strncmp(actual->id, "NO", 2) == 0)
	{
		if (pars->no == NULL)
		{
			pars->no = actual->content;
			// pars->no = ft_strdup(actual->content);
			// if (!pars->no)
			// {
			// 	return (write_error("Malloc error", actual->content, 1));
			// } // SI BESOIN DE MALLOC POUR FREE LA LISTE
			printf("Valid NO element registered %s\n", actual->content);
		}
		else
		{
			printf("actual = %s\n", pars->no);
			return (write_error("NO redefined", actual->content, 1));
		}
	}
	return (0);
}

int	fill_so(t_pars *pars, t_list *actual)
{
	if (ft_strncmp(actual->id, "SO", 2) == 0)
	{
		if (pars->so == NULL)
		{
			pars->so = actual->content;
			printf("Valid SO element registered %s\n", actual->content);
		}
		else
		{
			return (write_error("SO redefined", actual->content, 1));
		}
	}
	return (0);
}

int	fill_we(t_pars *pars, t_list *actual)
{
	if (ft_strncmp(actual->id, "WE", 2) == 0)
	{
		if (pars->we == NULL)
		{
			pars->we = actual->content;
			printf("Valid WE element registered %s\n", actual->content);
		}
		else
		{
			return (write_error("WE redefined", actual->content, 1));
		}
	}
	return (0);
}

int	fill_ea(t_pars *pars, t_list *actual)
{
	if (ft_strncmp(actual->id, "EA", 2) == 0)
	{
		if (pars->ea == NULL)
		{
			pars->ea = actual->content;
			printf("Valid EA element registered %s\n", actual->content);
		}
		else
		{
			return (write_error("EA redefined", actual->content, 1));
		}
	}
	return (0);
}

int	fill_colors(t_pars *pars, t_list *actual)
{
	if (ft_strncmp(actual->id, "F", 1) == 0)
	{
		if (pars->floor_color == NULL)
		{
			pars->floor_color = actual->content;
			printf("Valid floor element registered %s\n", actual->content); //
		}
		else
		 	return (write_error("F color redefined", actual->content, 1));
	}
	if (ft_strncmp(actual->id, "C", 1) == 0)
	{
		if (pars->ceiling_color == NULL)
		{
			pars->ceiling_color = actual->content;
			printf("Valid ceiling element registered %s\n", actual->content); //
		}
		else
		 	return (write_error("C color redefined", actual->content, 1));
	}
	return (0);
}
