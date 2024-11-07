/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setting_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: endoliam <endoliam@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 13:21:24 by endoliam          #+#    #+#             */
/*   Updated: 2024/11/07 17:20:05 by endoliam         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int	calcul_cursorx(t_data *data, int cursor)
{
	return (cursor * data->menu.setting_menu.barre.scale_x
		+ data->menu.setting_menu.barre.x
		- ((data->menu.setting_menu.cursor->anim->frame.height) * 0.5
			* data->menu.setting_menu.cursor->scale_x));
}

int		set_flag_color(t_data *data, t_color_cursor cursor, int flag)
{
	if (cursor.r == data->menu.setting_menu.cursor_floor.r
	&& cursor.g == data->menu.setting_menu.cursor_floor.g
	&& cursor.b == data->menu.setting_menu.cursor_floor.b)
		flag++;
	return (flag);
}

void	put_color_cursor(t_data *data, int basex, int basey,
	t_color_cursor cursor)
{
	int		flag;

	data->menu.setting_menu.barre.x = data->menu.setting_menu.speed.x
		+ basex;
	data->menu.setting_menu.barre.y = basey;
	put_button(data, &data->menu.setting_menu.barre, BAR_ANIMATION);
	data->menu.setting_menu.cursor->x = calcul_cursorx(data, cursor.r);
	data->menu.setting_menu.cursor->y = basey
		+ (30 * data->menu.setting_menu.barre.scale_y);
	flag = RED_SKY_ANIMATION;
	flag = set_flag_color(data, cursor, flag);
	put_button(data, data->menu.setting_menu.cursor, flag);
	data->menu.setting_menu.barre.y += 60
		* data->menu.setting_menu.barre.scale_y;
	put_button(data, &data->menu.setting_menu.barre, BAR_ANIMATION);
	data->menu.setting_menu.cursor->x = calcul_cursorx(data, cursor.g);
	data->menu.setting_menu.cursor->y = data->menu.setting_menu.barre.y
		+ (30 * data->menu.setting_menu.barre.scale_y);
	flag = GREEN_SKY_ANIMATION;
	flag = set_flag_color(data, cursor, flag);
	put_button(data, data->menu.setting_menu.cursor, flag);
	data->menu.setting_menu.barre.y += 60
		* data->menu.setting_menu.barre.scale_y;
	put_button(data, &data->menu.setting_menu.barre, BAR_ANIMATION);
	data->menu.setting_menu.cursor->x = calcul_cursorx(data, cursor.b);
	data->menu.setting_menu.cursor->y = data->menu.setting_menu.barre.y
		+ (30 * data->menu.setting_menu.barre.scale_y);
	flag = BLUE_SKY_ANIMATION;
	flag = set_flag_color(data, cursor, flag);
	put_button(data, data->menu.setting_menu.cursor, flag);
}

void	put_cursor(t_data *data, int basex, int basey, int cursor)
{
	data->menu.setting_menu.barre.x = basex + 0.1 * data->win_height;
	data->menu.setting_menu.barre.y = basey;
	put_button(data, &data->menu.setting_menu.barre, BAR_ANIMATION);
	data->menu.setting_menu.cursor->x = calcul_cursorx(data, cursor);
	data->menu.setting_menu.cursor->y = basey
		+ (30 * data->menu.setting_menu.barre.scale_y);
	put_button(data, data->menu.setting_menu.cursor, CURS_ANIMATION);
}

void	add_colors_quare_setting(t_data *data, int basex, int basey,
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
	add_colors_quare_setting(data, basex + data->win_width * 0.03,
		basey, data->sprites.ceiling);
	add_colors_quare_setting(data, basex
		+ data->menu.setting_menu.color.anim->frame.height
		* data->menu.setting_menu.color.scale_x * 1.2,
		basey, data->sprites.floor);
	update_frame(data, &data->menu.icone, 15);
}

void	setting_menu(t_data *data)
{
	int		x;
	int		cursor;

	x = (data->menu.setting_menu.speed.anim->frame.width
			* data->menu.setting_menu.speed.scale_x);
	init_img(data);
	put_background(data, &data->menu.background);
	put_button(data, &data->menu.setting_menu.speed, SPEED_ANIMATION);
	cursor = data->menu.setting_menu.cursor_speed
		* data->menu.setting_menu.barre.scale_x;
	put_cursor(data, data->menu.setting_menu.speed.x + x,
		data->menu.setting_menu.speed.y, cursor);
	put_button(data, &data->menu.setting_menu.cam, CAM_ANIMATION);
	cursor = data->menu.setting_menu.cursor_cam
		* data->menu.setting_menu.barre.scale_x;
	put_cursor(data, data->menu.setting_menu.cam.x + x,
		data->menu.setting_menu.cam.y, cursor);
	add_color_content(data);
	destroy_img(data, data->menu.background.x, data->menu.background.y);
}
