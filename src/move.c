/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: endoliam <endoliam@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 14:09:55 by endoliam          #+#    #+#             */
/*   Updated: 2024/09/13 17:57:31 by endoliam         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	cam_rotate(t_data *data, double rotspeed , int flag)
{
	double		olddirx;
	double		oldplanex;

	if (flag == 'w')
	{
		olddirx = data->player.dirx;
		data->player.dirx = data->player.dirx * cos(rotspeed) - data->player.diry * sin(rotspeed);
		data->player.diry = olddirx * sin(rotspeed) + data->player.diry * cos(rotspeed);
		oldplanex = data->player.planex;
		data->player.planex = data->player.planex * cos(rotspeed) - data->player.planey * sin(rotspeed);
		data->player.planey = oldplanex * sin(rotspeed) + data->player.planey * cos(rotspeed);
	}
	else if (flag == 'h')
	{
		if (data->player.pitch + rotspeed < 0.8 && data->player.pitch + rotspeed > -0.7)
			data->player.pitch += rotspeed;
	}
}

void	find_keyplayer_move(t_data *data)
{
	if (data->key.z)
		player_move(data, data->player.dirx, data->player.diry);
	if (data->key.s)
		player_move(data, -data->player.dirx, -data->player.diry);
	if (data->key.q)
		player_move(data, -data->player.diry, data->player.dirx);
	if (data->key.d)
		player_move(data, data->player.diry, -data->player.dirx);
	else if (!data->key.tab && !data->key.c)
		data->player.movespeed = data->player.speed;
	if (data->key.space)
	{
		data->player.posz += data->player.jump_speed;
        data->player.jump_speed += data->player.gravity;
		if (data->player.posz >= data->player.initz)
		{
			data->player.posz = data->player.initz;
			data->key.space = 0;
			data->player.jump_speed  = 0;
		}
	}
	if (data->key.tab && !data->key.c)
		data->player.movespeed = data->player.speed * 2;
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

int	move(t_data *data)
{
	find_keyplayer_move(data);
	find_keycam_move(data);
	//data->player.wallheight += 0.002;
	raycasting(data);
	return (0);
}