/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: endoliam <endoliam@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 12:38:27 by endoliam          #+#    #+#             */
/*   Updated: 2024/11/13 11:45:38 by endoliam         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"
#include "utils.h"

bool	is_player_init_pos(char c, t_move *player)
{
	if (c == 'N')
	{
		player->dirx = -1;
		player->planey = player->fov / 90;
		return (true);
	}
	else if (c == 'S')
	{
		player->dirx = 1;
		player->planey = -player->fov / 90;
		return (true);
	}
	else if (c == 'E')
	{
		player->diry = 1;
		player->planex = player->fov / 90;
		return (true);
	}
	else if (c == 'W')
	{
		player->diry = -1;
		player->planex = -player->fov / 90;
		return (true);
	}
	return (false);
}

void	init_player(char **map, t_move *player)
{
	int		i;
	int		j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (is_player_init_pos(map[i][j], player))
			{
				player->posx = i;
				player->posy = j;
				map[i][j] = '0';
			}
			j++;
		}
		i++;
	}
}

void	init_game(t_data *data)
{
	ft_memset(&data->player, 0, sizeof(t_move));
	data->player.fov = 60;
	init_player(data->map, &data->player);
	data->player.posx += 0.5;
	data->player.posy += 0.5;
	data->player.gravity = 0.6;
	data->player.movespeed = 0.05;
	data->player.speed = data->player.movespeed;
	data->player.rotspeed = 0.001;
	data->player.wallheight = 5;
	data->statement = PLAY;
}
