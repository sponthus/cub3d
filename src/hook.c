/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: endoliam <endoliam@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 14:26:21 by endoliam          #+#    #+#             */
/*   Updated: 2024/10/14 11:40:28 by endoliam         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h" 

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
	if (keycode == XK_z)
		data->key.w = 1;
	if (keycode == XK_s)
		data->key.s = 1;
	if (keycode == XK_q)
		data->key.a = 1;
	if (keycode == XK_d)
		data->key.d = 1;
	if (keycode == XK_Shift_L)
		data->key.shift_l = 1;
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

void	unset_keyplayer(int keycode, t_data *data)
{
	if (keycode == XK_z)
		data->key.w = 0;
	if (keycode == XK_s)
		data->key.s = 0;
	if (keycode == XK_q)
		data->key.a = 0;
	if (keycode == XK_d)
		data->key.d = 0;
	if (keycode == XK_Shift_L)
		data->key.shift_l = 0;
}

void	unset_keycam(int keycode, t_data *data)
{
	if (keycode == XK_Left)
		data->key.left = 0;
	if (keycode == XK_Right)
		data->key.right = 0;
	if (keycode == XK_Up)
		data->key.up = 0;
	if (keycode == XK_Down)
		data->key.down = 0;
}

int	key_release(int keycode, t_data *data)
{
	unset_keycam(keycode, data);
	unset_keyplayer(keycode, data);
	return (0);
}

int	key_press(int keycode, t_data *data)
{
	if (keycode == XK_Escape)
	{
		if (data->display.ptr1.img)
			mlx_destroy_image(data->mlx, data->display.ptr1.img);
		// mlx_destroy_window(data->mlx, data->win);
		// mlx_destroy_display(data->mlx);
		// free_data(data);
		free_data(data);
		exit (EXIT_SUCCESS);
	}
	set_keyplayer(keycode, data);
	set_keycam(keycode, data);
	return (0);
}
