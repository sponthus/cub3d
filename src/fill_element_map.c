/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_element_map.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sponthus <sponthus@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 14:41:52 by sponthus          #+#    #+#             */
/*   Updated: 2024/09/17 12:10:26 by sponthus         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

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

int	fill_map(t_data *data, t_list *actual)
{
	char	**map;
	int		i;

	i = 0;
	map = NULL;
	if (!actual || actual->map == false)
		return (write_error("No map detected in file", NULL, 1));
	map = malloc(sizeof (char *) * (map_size(actual) + 1));
	if (!map)
		return (write_error("Malloc error", "map", 1));
	while (actual)
	{
		map[i] = ft_strdup(actual->content);
		if (!map[i])
		{
			// fonction free de la map selon i
			return (write_error("Malloc error", "map", 1));
		}
		i++;
		actual = actual->next;
	}
	map[i] = NULL;
	data->map = map;
	return (0);
}
