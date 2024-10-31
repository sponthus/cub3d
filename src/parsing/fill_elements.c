/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_elements.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sponthus <sponthus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 14:29:55 by sponthus          #+#    #+#             */
/*   Updated: 2024/10/31 14:16:22 by sponthus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "errors.h"
#include "parsing.h"

int	fill_no(t_pars *pars, t_list *actual)
{
	if (ft_strncmp(actual->id, "NO", 2) == 0)
	{
		if (pars->no == NULL)
			pars->no = actual->content;
		else
			return (write_err(ERR_RED, actual->content, "NO", 1));
	}
	return (0);
}

int	fill_so(t_pars *pars, t_list *actual)
{
	if (ft_strncmp(actual->id, "SO", 2) == 0)
	{
		if (pars->so == NULL)
			pars->so = actual->content;
		else
			return (write_err(ERR_RED, actual->content, "SO", 1));
	}
	return (0);
}

int	fill_we(t_pars *pars, t_list *actual)
{
	if (ft_strncmp(actual->id, "WE", 2) == 0)
	{
		if (pars->we == NULL)
			pars->we = actual->content;
		else
			return (write_err(ERR_RED, actual->content, "WE", 1));
	}
	return (0);
}

int	fill_ea(t_pars *pars, t_list *actual)
{
	if (ft_strncmp(actual->id, "EA", 2) == 0)
	{
		if (pars->ea == NULL)
			pars->ea = actual->content;
		else
			return (write_err(ERR_RED, actual->content, "EA", 1));
	}
	return (0);
}

int	fill_colors(t_pars *pars, t_list *actual)
{
	if (ft_strncmp(actual->id, "F", 1) == 0)
	{
		if (pars->floor_color == NULL)
			pars->floor_color = actual->content;
		else
			return (write_err(ERR_RED, actual->content, "F", 1));
	}
	if (ft_strncmp(actual->id, "C", 1) == 0)
	{
		if (pars->ceiling_color == NULL)
			pars->ceiling_color = actual->content;
		else
			return (write_err(ERR_RED, actual->content, "C", 1));
	}
	return (0);
}
