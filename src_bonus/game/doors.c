/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sponthus <sponthus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 13:33:42 by sponthus          #+#    #+#             */
/*   Updated: 2024/10/30 14:53:33 by sponthus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	print_map(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (data->map[i])
	{
		j = 0;
		while (data->map[i][j])
		{
			write(1, &data->map[i][j], 1);
			j++;
		}
		write(1, "\n", 1);
		i++;
	}
}

// void	doors_message(t_data *data)
// {
// 	pl = data->player;
// 	while (i < 3)
// 	{
// 		j = -2;
// 		while (j < 3)
// 		{
// 			if (data->map[(int)pl.posx + i][(int)pl.posy + j]
// 				&& data->map[(int)pl.posx + i][(int)pl.posy + j] == 'D')
// 				// mg
// 			else if (data->map[(int)pl.posx + i][(int)pl.posy + j]
// 				&& data->map[(int)pl.posx + i][(int)pl.posy + j] == 'O')
// 			{
// 				if (i != 0 || j != 0 || (i == 0 && j != 0)
// 					|| (j == 0 && i != 0))
// 					// msg
// 			}
// 			j++;
// 		}
// 		i++;
// 	}
// }

void	doors(t_data *data)
{
	int		i;
	int		j;
	t_move	pl;	

	i = -2;
	pl = data->player;
	while (i < 3)
	{
		j = -2;
		while (j < 3)
		{
			if (data->map[(int)pl.posx + i][(int)pl.posy + j]
				&& data->map[(int)pl.posx + i][(int)pl.posy + j] == 'D')
				data->map[(int)pl.posx + i][(int)pl.posy + j] = 'O';
			else if (data->map[(int)pl.posx + i][(int)pl.posy + j]
				&& data->map[(int)pl.posx + i][(int)pl.posy + j] == 'O')
			{
				if (i != 0 || j != 0 || (i == 0 && j != 0)
					|| (j == 0 && i != 0))
					data->map[(int)pl.posx + i][(int)pl.posy + j] = 'D';
			}
			j++;
		}
		i++;
	}
}
