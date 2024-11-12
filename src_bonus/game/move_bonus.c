/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sponthus <sponthus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 14:09:55 by endoliam          #+#    #+#             */
/*   Updated: 2024/11/12 10:09:20 by sponthus         ###   ########.fr       */
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
		&& (data->map[(int)(verifx)][(int)(data->player.posy)] == '0'
		|| data->map[(int)(verifx)][(int)(data->player.posy)] == 'O'))
		data->player.posx = newx;
	if ((data->map[(int)(data->player.posx)][(int)(verify)] == '0'
		|| data->map[(int)(data->player.posx)][(int)(verify)] == 'O'))
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

void	move(t_data *data)
{
	find_keyplayer_move(data);
	find_keycam_move(data);
	find_keyaction(data);
	mouse_setting(data);
	raycasting(data);
}
