/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setting_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: endoliam <endoliam@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 13:21:24 by endoliam          #+#    #+#             */
/*   Updated: 2024/11/08 14:51:11 by endoliam         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	put_color_cursor(t_data *data, int basex, int basey,
	t_color_cursor cursor)
{
	put_line(data, data->menu.setting_menu.speed.x
		+ basex, basey, cursor.r);
	put_cursor(data, RED_SKY_ANIMATION, &cursor);
	basey += 60
		* data->menu.setting_menu.barre.scale_y;
	put_line(data, data->menu.setting_menu.speed.x
		+ basex, basey, cursor.g);
	put_cursor(data, GREEN_SKY_ANIMATION, &cursor);
	basey += 60
		* data->menu.setting_menu.barre.scale_y;
	put_line(data, data->menu.setting_menu.speed.x
		+ basex, basey, cursor.b);
	put_cursor(data, BLUE_SKY_ANIMATION, &cursor);
}

void	add_colors_square_setting(t_data *data, int basex, int basey,
		unsigned int color)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (x < data->win_width * 0.05)
	{
		y = 0;
		while (y < data->win_width * 0.05)
		{
			my_mlx_pixel_put(&data->display.ptr1, x + basex, y + basey, color);
			y++;
		}
		x++;
	}
	if (color == data->sprites.ceiling)
		put_color_cursor(data, basex, basey + y,
			data->menu.setting_menu.cursor_sky);
	else
		put_color_cursor(data, basex, basey + y,
			data->menu.setting_menu.cursor_floor);
}

void	add_color_content(t_data *data)
{
	int	basex;
	int	basey;

	put_button(data, &data->menu.setting_menu.color, COLOR_ANIMATION);
	basey = data->menu.setting_menu.color.y + data->win_height * 0.2;
	basex = data->menu.setting_menu.color.x ;
	add_colors_square_setting(data, basex + data->win_width * 0.03,
		basey, data->sprites.ceiling);
	add_colors_square_setting(data, basex
		+ data->menu.setting_menu.color.anim->frame.height
		* data->menu.setting_menu.color.scale_x * 1.2,
		basey, data->sprites.floor);
	update_frame(data, &data->menu.icone, 15);
}

void	add_speeds_cursors(t_data *data)
{
	int	cursor;
	int	x;

	x = (data->menu.setting_menu.speed.anim->frame.width
			* data->menu.setting_menu.speed.scale_x) + (0.1 * data->win_height);
	put_button(data, &data->menu.setting_menu.speed, SPEED_ANIMATION);
	cursor = data->menu.setting_menu.cursor_speed
		* data->menu.setting_menu.barre.scale_x;
	put_line(data, data->menu.setting_menu.speed.x + x,
		data->menu.setting_menu.speed.y, cursor);
	put_cursor(data, CURS_SPEED_ANIMATION, NULL);
	put_button(data, &data->menu.setting_menu.cam, CAM_ANIMATION);
	cursor = data->menu.setting_menu.cursor_cam
		* data->menu.setting_menu.barre.scale_x;
	put_line(data, data->menu.setting_menu.cam.x + x,
		data->menu.setting_menu.cam.y, cursor);
	put_cursor(data, CURS_CAM_ANIMATION, NULL);
}

void	setting_menu(t_data *data)
{
	init_img(data);
	if (data->display.ptr1.img)
	{
		put_background(data, &data->menu.background);
		add_speeds_cursors(data);
		add_color_content(data);
		destroy_img(data, data->menu.background.x, data->menu.background.y);
	}
}
