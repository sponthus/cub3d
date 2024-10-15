/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sponthus <sponthus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 14:41:52 by sponthus          #+#    #+#             */
/*   Updated: 2024/10/15 13:56:52 by sponthus         ###   ########.fr       */
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

void	copy_map(char *dst, char *src)
{
	int	i;

	i = 0;
	while (src[i] && dst[i])
	{
		dst[i] = src[i];
		i++;
	}
}

int	resize_map(t_data *data)
{
	int		len;
	int		i;
	char	*new;

	len = map_length(data);
	i = 0;
	while (data->map[i])
	{
		if (ft_strlen(data->map[i]) < len)
		{
			new = malloc(len + 1 * sizeof (char));
			if (!new)
				return (write_err(ERR_MALLOC, "map", NULL, 1));
			ft_memset(new, ' ', len + 1);
			new[len] = '\0';
			copy_map(new, data->map[i]);
			free(data->map[i]);
			data->map[i] = new;
		}
		i++;
	}
	return (0);
}

int	fill_map(t_data *data, t_list *actual)
{
	char	**map;
	int		i;

	i = 0;
	map = NULL;
	if (!actual || actual->map == false)
		return (write_err(ERR_NO_ELEM, "map", NULL, 1));
	map = malloc(sizeof (char *) * (list_map_size(actual) + 1));
	if (!map)
		return (write_err(ERR_MALLOC, "map", NULL, 1));
	while (actual)
	{
		map[i] = ft_strdup(actual->content);
		if (!map[i])
		{
			free_split(map, i); // Check that plz
			return (write_err(ERR_MALLOC, "map", NULL, 1));
		}
		i++;
		actual = actual->next;
	}
	map[i] = NULL;
	data->map = map;
	return (0);
}

bool	fill_file_content(t_data *data, t_pars *pars)
{
	t_list	*actual;

	actual = pars->lst_file;
	while (actual)
	{
		if (what_is_it(actual) == true)
		{
			if (actual->map)
				break ;
			if (actual->empty == false && resize_content(actual) != 0)
				return (false);
			if (fill_element(pars, actual) != 0)
				return (false);
			actual = actual->next;
		}
		else
			return (false);
	}
	if (fill_map(data, actual) != 0)
		return (false);
	if (resize_map(data) != 0)
		return (false);
	return (true);
}
