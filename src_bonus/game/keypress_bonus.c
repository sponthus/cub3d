/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keypress_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sponthus <sponthus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 14:26:21 by endoliam          #+#    #+#             */
/*   Updated: 2024/10/30 13:33:37 by sponthus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h" 

void	set_keysit(t_data *data)
{
	if (data->player.posz == 0 && !data->key.space)
	{
		data->key.c = 1;
		data->player.posz = data->win_height / 4;
		data->player.movespeed = data->player.speed / 2;
	}
	else if (!data->key.space)
	{
		data->key.c = 0;
		data->player.posz = 0;
	}
}

void	set_keyjump(t_data *data)
{
	if (!data->key.space)
	{
		data->key.space = 1;
		data->player.jump_speed = -4;
		data->player.initz = data->player.posz;
	}
}

void	set_keyplayer(int keycode, t_data *data)
{
	if (keycode == XK_w)
		data->key.w = 1;
	if (keycode == XK_s)
		data->key.s = 1;
	if (keycode == XK_a)
		data->key.a = 1;
	if (keycode == XK_d)
		data->key.d = 1;
	if (keycode == XK_Shift_L)
		data->key.shift_l = 1;
	if (keycode == XK_o)
		doors(data);
}

void	set_keycam(int keycode, t_data *data)
{
	if (keycode == XK_Left)
		data->key.left = 1;
	if (keycode == XK_Right)
		data->key.right = 1;
	if (keycode == XK_Up)
		data->key.up = 1;
	if (keycode == XK_Down)
		data->key.down = 1;
	if (keycode == XK_c)
		set_keysit(data);
	if (keycode == XK_space)
		set_keyjump(data);
}

int	key_press(int keycode, t_data *data)
{
	if (keycode == XK_Escape)
		destroy_game(data, EXIT_SUCCESS);
	if (keycode == XK_Tab)
	{
		if (data->statement == PLAY)
		{
			data->key.tab = 1;
			data->statement = PAUSE;
		}
		else if (data->statement == PAUSE)
			data->statement = PLAY;
	}
	if (data->statement == PLAY)
	{
		set_keyplayer(keycode, data);
		set_keycam(keycode, data);
	}
	if (data->statement == PAUSE)
	{
		if (keycode == XK_KP_Enter || keycode == XK_Return)
		{
			if (data->menu.state_menu == RESUME)
				data->statement = PLAY;
			if (data->menu.state_menu == EXIT)
				destroy_game(data, EXIT_SUCCESS);
		}
		if (keycode == XK_Up)
		{
			if (data->menu.state_menu != RESUME)
				data->menu.state_menu--;
		}
		if (keycode == XK_Down)
		{
			if (data->menu.state_menu != EXIT)
				data->menu.state_menu++;
		}
	}
	return (0);
}
