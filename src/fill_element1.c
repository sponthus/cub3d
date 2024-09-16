/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_element1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sponthus <sponthus@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 14:29:55 by sponthus          #+#    #+#             */
/*   Updated: 2024/09/16 14:43:00 by sponthus         ###   ########lyon.fr   */
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
			printf("Valid NO element registered %s\n", actual->content);
		}
		else
		{
			printf("actual = %s\n", pars->no);
			write_error("NO redefined : ", actual->content);
		 	return (1);
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
			write_error("SO redefined : ", actual->content);
		 	return (1);
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
			write_error("WE redefined : ", actual->content);
		 	return (1);
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
			write_error("EA redefined : ", actual->content);
		 	return (1);
		}
	}
	return (0);
}

int	fill_element(t_pars *pars, t_list *actual)
{
	if (fill_no(pars, actual) == 1)
		return (1);
	if (fill_so(pars, actual) == 1)
		return (1);
	if (fill_we(pars, actual) == 1)
		return (1);
	if (fill_ea(pars, actual) == 1)
		return (1);
	if (fill_colors(pars, actual) == 1)
		return (1);
	return (0);
}
