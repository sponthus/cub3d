/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_is_valid_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sponthus <sponthus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 13:02:15 by sponthus          #+#    #+#             */
/*   Updated: 2024/10/30 10:56:10 by sponthus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

bool	only_one_map(t_data *data)
{
	int		i;
	bool	empty;

	i = 0;
	empty = false;
	while (data->map[i])
	{
		replace_whitespaces(data->map[i]);
		if (empty_mapline(data->map[i]))
		{
			empty = true;
			i++;
			while (data->map[i])
			{
				if (empty_mapline(data->map[i]) == false)
					return (write_err(ERR_COUNT, EXP_1, "map", false));
				i++;
			}
			if (!data->map[i])
				return (true);
		}
		i++;
	}
	return (true);
}

bool	only_one_player(t_data *data)
{
	bool	player;
	int		i;
	int		j;

	player = false;
	i = 0;
	while (data->map[i])
	{
		j = 0;
		while (data->map[i][j])
		{
			if (is_charset(data->map[i][j], "NSEW"))
			{
				if (player == true)
					return (write_err(ERR_COUNT, EXP_1, "player", false));
				else
					player = true;
			}
			j++;
		}
		i++;
	}
	if (player == false)
		return (write_err(ERR_NO_ELEM, "player", NULL, false));
	return (true);
}

bool	closed_map(t_data *data, int map_size)
{
	int		i;
	int		j;

	i = 0;
	while (data->map[i])
	{
		j = 0;
		while (data->map[i][j])
		{
			if (data->map[i][j] == '0')
			{
				if (i == 0 || j == 0 || j == ft_strlen(data->map[i])
					|| i == map_size)
					return (false);
				if (data->map[i - 1][j] == ' ' || data->map[i + 1][j] == ' '
					|| data->map[i][j + 1] == ' ' || data->map[i][j + 1] == ' ')
					return (false);
			}
			j++;
		}
		i++;
	}
	return (true);
}

void	replace_spaces(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (data->map[i])
	{
		j = 0;
		while (data->map[i][j])
		{
			if (data->map[i][j] == ' ' || data->map[i][j] == '\n')
				data->map[i][j] = '1';
			j++;
		}
		i++;
	}
}

bool	is_valid_map(t_data *data)
{
	int	i;

	i = map_size(data);
	if (only_one_map(data) == false)
		return (false);
	if (only_one_player(data) == false)
		return (false);
	if (closed_map(data, i) == false)
		return (write_err("Map is not closed", NULL, NULL, false));
	replace_spaces(data);
	return (true);
}
