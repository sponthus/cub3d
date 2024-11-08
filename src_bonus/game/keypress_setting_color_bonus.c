/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keypress_setting_color_bonus.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: endoliam <endoliam@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 14:08:33 by endoliam          #+#    #+#             */
/*   Updated: 2024/11/07 17:29:43 by endoliam         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h" 

unsigned int	move_rgb_and_color(t_data *data, int x,
	unsigned int c, int *cursor)
{
	if (c + (unsigned int)x > 0 && c + (unsigned int)x <= 255)
	{
		c += (unsigned int)x;
		*(cursor) += x
			* (int)((data->menu.setting_menu.barre.anim->frame.height) / 255);
	}
	return (c);
}

unsigned int	move_rgb(t_data *data, unsigned int color, int x,
	t_color_cursor *cursor)
{
	unsigned int	r;
	unsigned int	g;
	unsigned int	b;

	r = (color >> 16) & 0xFF;
	g = (color >> 8) & 0xFF;
	b = color & 0xFF;
	if (data->menu.setting_menu.color_state == RED)
		r = move_rgb_and_color(data, x, r, &cursor->r);
	else if (data->menu.setting_menu.color_state == GREEN)
		g = move_rgb_and_color(data, x, g, &cursor->g);
	else if (data->menu.setting_menu.color_state == BLUE)
		b = move_rgb_and_color(data, x, b, &cursor->b);
	return (r << 16 | g << 8 | b);
}

void	keypress_move_color(int keycode, t_data *data)
{
	if (keycode == XK_Left)
	{
		if (data->menu.setting_menu.setting_state == COLOR_SKY)
			data->sprites.ceiling = move_rgb(data, data->sprites.ceiling,
					-1, &data->menu.setting_menu.cursor_sky);
		else
			data->sprites.floor = move_rgb(data, data->sprites.floor,
					-1, &data->menu.setting_menu.cursor_floor);
	}
	else if (keycode == XK_Right)
	{
		if (data->menu.setting_menu.setting_state == COLOR_SKY)
			data->sprites.ceiling = move_rgb(data, data->sprites.ceiling,
					1, &data->menu.setting_menu.cursor_sky);
		else
			data->sprites.floor = move_rgb(data, data->sprites.floor,
					1, &data->menu.setting_menu.cursor_floor);
	}
}
