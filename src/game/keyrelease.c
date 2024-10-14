/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyrelease.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: endoliam <endoliam@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 14:19:31 by endoliam          #+#    #+#             */
/*   Updated: 2024/10/14 14:26:53 by endoliam         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h" 

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
