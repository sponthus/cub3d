/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sponthus <sponthus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 13:33:42 by sponthus          #+#    #+#             */
/*   Updated: 2024/10/31 13:02:28 by sponthus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int	check_line(t_data *data, int i, int j)
{
	t_move	pl;

	pl = data->player;
	if ((int)pl.posx + i > map_length(data)
		|| (int)pl.posy + j > map_size(data) || (int)pl.posx + i < 0
		|| (int)pl.posy + j < 0)
		return (2);
	if (data->map[(int)pl.posx + i][(int)pl.posy + j])
	{
		if ((data->map[(int)pl.posx + i][(int)pl.posy + j] == 'D' 
		|| data->map[(int)pl.posx + i][(int)pl.posy + j] == 'O')
		&& (i != 0 || j != 0 || (i == 0 && j != 0) || (j == 0 && i != 0)))
		{
			return (1);
		}
	}
	else
		return (2);
	return (0);
}

void	doors_message(t_data *data)
{
	int		i;
	int		j;
	t_move	pl;

	i = -3;
	pl = data->player;
	while (++i < 3)
	{
		j = -3;
		while (++j < 3)
		{
			if (check_line(data, i, j) != 0)
			{
				if (check_line(data, i, j) == 1)
				{
					mlx_string_put(data->mlx, data->win, data->win_height, \
					data->win_width * 0.5, COL_MSG, DOOR_MSG);
				}
				return ;
			}
		}
	}
}

void	doors(t_data *data)
{
	int		i;
	int		j;
	t_move	pl;

	i = -3;
	pl = data->player;
	while (++i < 3)
	{
		j = -3;
		while (++j < 3)
		{
			if (data->map[(int)pl.posx + i][(int)pl.posy + j])
			{
				if (data->map[(int)pl.posx + i][(int)pl.posy + j] == 'D')
					data->map[(int)pl.posx + i][(int)pl.posy + j] = 'O';
				else if (data->map[(int)pl.posx + i][(int)pl.posy + j] == 'O')
					if (i != 0 || j != 0 || (i == 0 && j != 0)
						|| (j == 0 && i != 0))
						data->map[(int)pl.posx + i][(int)pl.posy + j] = 'D';
			}
		}
	}
}
