/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sponthus <sponthus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 14:09:55 by endoliam          #+#    #+#             */
/*   Updated: 2024/10/30 10:41:00 by sponthus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	player_move(t_data *data, double dirx, double diry)
{
	double		newx;
	double		newy;
	double		verifx;
	double		verify;

	verifx = data->player.posx + dirx * (data->player.movespeed * 2);
	verify = data->player.posy + diry * (data->player.movespeed * 2);
	newx = data->player.posx + dirx * data->player.movespeed;
	newy = data->player.posy + diry * data->player.movespeed;
	if (data->map[(int)(verifx)][(int)(data->player.posy)]
		&& data->map[(int)(verifx)][(int)(data->player.posy)] == '0')
		data->player.posx = newx;
	if (data->map[(int)(data->player.posx)][(int)(verify)]
		&& data->map[(int)(data->player.posx)][(int)(verify)] == '0')
		data->player.posy = newy;
}

void	cam_rotate(t_data *data, double rotspeed, int flag)
{
	double		olddirx;
	double		oldplanex;

	if (flag == 'w')
	{
		olddirx = data->player.dirx;
		data->player.dirx *= cos(rotspeed);
		data->player.dirx -= data->player.diry * sin(rotspeed);
		data->player.diry = olddirx * sin(rotspeed)
			+ data->player.diry * cos(rotspeed);
		oldplanex = data->player.planex;
		data->player.planex *= cos(rotspeed);
		data->player.planex -= data->player.planey * sin(rotspeed);
		data->player.planey = oldplanex * sin(rotspeed)
			+ data->player.planey * cos(rotspeed);
	}
	else if (flag == 'h')
	{
		if (data->player.pitch + rotspeed < 0.8
			&& data->player.pitch + rotspeed > -0.7)
			data->player.pitch += rotspeed;
	}
}

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
	else if (!data->key.shift_l && !data->key.c)
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
	if (data->key.shift_l && !data->key.c)
		data->player.movespeed = data->player.speed * 3;
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

void	move(t_data *data)
{
	find_keyplayer_move(data);
	find_keycam_move(data);
	mouse_setting(data);
	//data->player.wallheight += 0.002;
	raycasting(data);
}
