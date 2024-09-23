/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_measure.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sponthus <sponthus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 11:09:26 by sponthus          #+#    #+#             */
/*   Updated: 2024/09/23 13:55:42 by sponthus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	map_length(t_data *data)
{
	int	i;
	int	max;
	int	len;

	max = 0;
	len = 0;
	i = 0;
	while (data->map[i])
	{
		len = ft_strlen(data->map[i]);
		if (len > max)
		{
			max = len;
		}
		i++;
	}
	return (max);
}

int	map_size(t_data *data)
{
	int		i;

	i = 0;
	while (data->map[i])
	{
		if (empty_mapline(data->map[i]))
		{
			break ;
		}
		i++;
	}
	return (i);
}

int	list_map_size(t_list *lst)
{
	int	i;

	i = 0;
	while (lst)
	{
		i++;
		lst = lst->next;
	}
	return (i);
}
