/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_menu_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sponthus <sponthus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 13:54:49 by endoliam          #+#    #+#             */
/*   Updated: 2024/11/12 10:21:13 by sponthus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	set_img_data(t_anim *element, int x, int y, int flag)
{
	if (flag == MEN_FLAG)
	{
		element->scale_x = WIN_WIDTH / SCALE_X;
		element->scale_y = WIN_HEIGHT / SCALE_Y;
	}
	else if (flag == SETTI_FLAG)
	{
		element->scale_x = WIN_WIDTH / SCALE_X * 0.8;
		element->scale_y = WIN_HEIGHT / SCALE_Y * 1.2;
	}
	element->x = x;
	element->y = y;
}

void	set_cursor_color(t_color_cursor *cursor, unsigned int color, int factor)
{
	cursor->r = (color >> 16 & 0xFF) * factor;
	cursor->g = (color >> 8 & 0xFF) * factor;
	cursor->b = (color & 0xFF) * factor;
}

void	init_setting_data(t_data *data)
{
	int		y;
	int		factor;

	factor = data->menu.setting_menu.barre.anim->frame.height / 255;
	data->menu.setting_menu.cursor = &data->menu.icone;
	set_img_data(&data->menu.setting_menu.speed,
		data->win_width,
		data->win_height - data->win_height, SETTI_FLAG);
	y = 80 * data->menu.setting_menu.speed.scale_y;
	set_img_data(&data->menu.setting_menu.cam,
		data->win_width,
		data->menu.setting_menu.speed.y + y, SETTI_FLAG);
	set_img_data(&data->menu.setting_menu.color,
		data->win_width,
		data->menu.setting_menu.cam.y + y, SETTI_FLAG);
	set_img_data(&data->menu.setting_menu.barre,
		0, 0, SETTI_FLAG);
	set_cursor_color(&data->menu.setting_menu.cursor_sky,
		data->sprites.ceiling, factor);
	set_cursor_color(&data->menu.setting_menu.cursor_floor,
		data->sprites.floor, factor);
}

void	set_data_menu(t_data *data)
{
	data->menu.background.x = 0;
	data->menu.background.y = data->win_height;
	set_img_data(&data->menu.resume,
		data->win_width - data->win_width * 0.7,
		data->win_height - data->win_height * 0.4, MEN_FLAG);
	set_img_data(&data->menu.setting,
		data->win_width - data->win_width * 0.3,
		data->win_height - data->win_height * 0.3, MEN_FLAG);
	set_img_data(&data->menu.exit,
		data->win_width - data->win_width * 0.7,
		data->win_height - data->win_height * 0.2, MEN_FLAG);
	data->menu.icone.scale_x = WIN_WIDTH / SCALE_X;
	data->menu.icone.scale_y = WIN_HEIGHT / SCALE_Y;
	init_setting_data(data);
}

void	init_menu(t_data *data)
{
	init_animation(data, &data->menu.background, MEN_BACK, 66);
	init_animation(data, &data->menu.setting, MEN_SET, 30);
	init_animation(data, &data->menu.resume, MEN_RES, 29);
	init_animation(data, &data->menu.exit, MEN_EXI, 31);
	init_animation(data, &data->menu.icone, MEN_IC, 10);
	init_animation(data, &data->menu.setting_menu.cam, MEN_CAM, 31);
	init_animation(data, &data->menu.setting_menu.speed, MEN_SPEED, 31);
	init_animation(data, &data->menu.setting_menu.color, MEN_COLOR, 32);
	init_animation(data, &data->menu.setting_menu.barre, MEN_BAR, 0);
	set_data_menu(data);
}
