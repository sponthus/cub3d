/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pause_menu_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: endoliam <endoliam@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 21:03:20 by endoliam          #+#    #+#             */
/*   Updated: 2024/11/08 12:26:59 by endoliam         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int	get_pixel_color(t_img *img, int y, int x)
{
	int	pixy;

	pixy = (y * img->height) * 0.01;
	if (x >= 0 && x < img->width && pixy >= 0 && pixy < img->height)
		return (*(int *)(img->addr + (img->ll * pixy) + (x * img->bpp / 8)));
	return (0x0);
}

void	add_to_background(t_data *data, t_anim *element, unsigned int c)
{
	int				x;
	int				y;
	unsigned int	color;
	int				index;

	x = 0;
	while (element && x <= element->anim->frame.width)
	{
		y = 0;
		while (element && y <= element->anim->frame.height)
		{
			index = ((element->y + y) * data->display.ptr1.ll)
				+ ((element->x + x) * (data->display.ptr1.bpp / 8));
			color = get_pixel_color((&element->anim->frame),
					y / element->scale_y, x / element->scale_x);
			if (color && (color & 0x00FFFFFF) != BLACK)
				*(unsigned int *)(data->display.ptr1.addr + index) = color;
			if ((c && color == 0x00085575) || (c && color == 0x00074B67))
				*(unsigned int *)(data->display.ptr1.addr + index) = c;
			y++;
		}
		x++;
	}
}

bool	is_anime_element(t_data *data, int flag)
{
	if (data->statement == SETTING_MENU)
	{
		if ((data->menu.setting_menu.setting_state == MOVESPEED 
				&& flag == SPEED_ANIMATION)
			|| (data->menu.setting_menu.setting_state == ROTSPEED
				&& flag == CAM_ANIMATION)
			|| (data->menu.setting_menu.setting_state == COLOR_SKY
				&& flag == COLOR_ANIMATION)
			||	(data->menu.setting_menu.setting_state == COLOR_FLOOR
				&& flag == COLOR_ANIMATION))
			return (true);
	}
	else if ((data->menu.state_menu == RESUME && flag == RESUME_ANIMATION)
		|| (data->menu.state_menu == SETTING && flag == SETTING_ANIMATION)
		|| (data->menu.state_menu == EXIT && flag == EXIT_ANIMATION))
		return (true);
	return (false);
}

bool	is_setting_icone(t_data *data, int flag)
{
	if (data->statement == SETTING_MENU)
	{
		if ((data->menu.setting_menu.setting_state == COLOR_SKY
				&& data->menu.setting_menu.color_state == RED
				&& flag == RED_SKY_ANIMATION)
			|| (data->menu.setting_menu.setting_state == COLOR_SKY
				&& data->menu.setting_menu.color_state == GREEN
				&& flag == GREEN_SKY_ANIMATION)
			|| (data->menu.setting_menu.setting_state == COLOR_SKY
				&& data->menu.setting_menu.color_state == BLUE
				&& flag == BLUE_SKY_ANIMATION)
			|| (data->menu.setting_menu.setting_state == COLOR_FLOOR
				&& data->menu.setting_menu.color_state == RED
				&& flag == RED_FLOOR_ANIMATION)
			|| (data->menu.setting_menu.setting_state == COLOR_FLOOR
				&& data->menu.setting_menu.color_state == GREEN
				&& flag == GREEN_FLOOR_ANIMATION)
			|| (data->menu.setting_menu.setting_state == COLOR_FLOOR
				&& data->menu.setting_menu.color_state == BLUE
				&& flag == BLUE_FLOOR_ANIMATION))
			return (true);
	}
	return (false);
}

void	put_button(t_data *data, t_anim *element, int flag)
{
	if (is_setting_icone(data, flag))
		add_to_background(data, element, FPS_COLOR);
	else
		add_to_background(data, element, 0);
	element->animspeed += data->player.frame * 100;
	if (is_anime_element(data, flag))
	{
		if (element->animspeed > 1 && element->anim->next)
		{
			element->animspeed = 0;
			element->anim = element->anim->next;
		}
		data->menu.icone.x = element->x
			- (element->anim->frame.width * element->scale_x);
		data->menu.icone.y = element->y;
	}
	else
	{
		if (element->animspeed > 1 && element->anim->index != 0)
			element->anim = element->anim->prev;
	}
}

void	put_background(t_data *data, t_anim *element)
{
	int				x;
	int				y;
	int				bgx;
	int				bgy;
	unsigned int	color;

	x = 0;
	y = 0;
		return ;
	while (x < data->win_width)
	{
		y = 0;
		bgx = (x * element->anim->frame.width) / data->win_width;
		while (y <= data->win_height)
		{
			bgy = (y * element->anim->frame.height) / data->win_height;
			color = *(int *)(element->anim->frame.addr
					+ (element->anim->frame.ll * bgy)
					+ (bgx * element->anim->frame.bpp / 8));
			my_mlx_pixel_put(&data->display.ptr1, x, y, color);
			y++;
		}
		x++;
	}
	update_frame(data, &data->menu.background, 60);
}

void	pause_game(t_data *data)
{
	init_img(data);
	mlx_mouse_show(data->mlx, data->win);
	if (data->display.ptr1.img)
	{
		put_background(data, &data->menu.background);
		put_button(data, &data->menu.resume, RESUME_ANIMATION);
		put_button(data, &data->menu.setting, SETTING_ANIMATION);
		put_button(data, &data->menu.exit, EXIT_ANIMATION);
		add_to_background(data, &data->menu.icone, 0);
		update_frame(data, &data->menu.icone, 10);
		destroy_img(data, data->menu.background.x, data->menu.background.y);
		if (data->menu.background.y > 0)
			data->menu.background.y -= data->win_height * 0.05;
	}
	update_frame_data(data);
}
