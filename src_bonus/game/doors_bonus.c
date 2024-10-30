/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sponthus <sponthus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 13:33:42 by sponthus          #+#    #+#             */
/*   Updated: 2024/10/30 16:25:06 by sponthus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

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
			if (data->map[(int)pl.posx + i][(int)pl.posy + j])
			{
				if (data->map[(int)pl.posx + i][(int)pl.posy + j] == 'D')
					mlx_string_put(data->mlx, data->win, data->win_height, \
					data->win_width * 0.5, COL_MSG, DOOR_MSG);
				else if (data->map[(int)pl.posx + i][(int)pl.posy + j] == 'O')
					if (i != 0 || j != 0 || (i == 0 && j != 0)
						|| (j == 0 && i != 0))
						mlx_string_put(data->mlx, data->win, data->win_height, \
						data->win_width * 0.5, COL_MSG, DOOR_MSG);
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
