/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyfind_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: endoliam <endoliam@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 15:19:30 by endoliam          #+#    #+#             */
/*   Updated: 2024/11/08 15:22:20 by endoliam         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	find_keyplayer_move(t_data *data)
{
	if (data->key.w)
		player_move(data, data->player.dirx, data->player.diry);
	if (data->key.s)
		player_move(data, -data->player.dirx, -data->player.diry);
	if (data->key.a)
		player_move(data, -data->player.diry, data->player.dirx);
	if (data->key.d)
		player_move(data, data->player.diry, -data->player.dirx);
}

void	find_keyaction(t_data *data)
{
	if (!data->key.shift_l && !data->key.c)
		data->player.movespeed = data->player.speed;
	if (data->key.space)
	{
		data->player.posz += data->player.jump_speed;
		data->player.jump_speed += data->player.gravity;
		if (data->player.posz >= data->player.initz)
		{
			data->player.posz = data->player.initz;
			data->key.space = 0;
			data->player.jump_speed = 0;
		}
	}
	if (data->key.shift_l && data->player.sprint && !data->key.c)
	{
		data->player.sprint = false;
		data->player.speed = data->player.movespeed;
		data->player.movespeed = data->player.movespeed * 1.9;
	}
}

void	find_keycam_move(t_data *data)
{
	if (data->key.right)
		cam_rotate(data, -data->player.rotspeed, 'w');
	if (data->key.left)
		cam_rotate(data, data->player.rotspeed, 'w');
	if (data->key.up)
		cam_rotate(data, -data->player.rotspeed, 'h');
	if (data->key.down)
		cam_rotate(data, data->player.rotspeed, 'h');
}
