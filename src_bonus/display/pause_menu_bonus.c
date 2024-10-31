/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pause_menu_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: endoliam <endoliam@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 21:03:20 by endoliam          #+#    #+#             */
/*   Updated: 2024/10/31 13:40:32 by endoliam         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"


int		get_pixel_color(t_img *img, int y, int x)
{
	int	pixy;

	pixy = (y * img->height) * 0.01;
	if (x >= 0 && x < img->width && pixy >= 0 && pixy < img->height)
		return (*(int *)(img->addr + (img->ll * pixy) + (x * img->bpp / 8)));
	return (0x0);
}

void	add_to_background(t_data *data, t_anim *element)
{
	int				x;
	int				y;
	int				bgx;
	int				bgy;
	unsigned int	color;
	int				index;

	x = 0;
	while(x <= element->anim->frame.width)
	{
		y = 0;
		bgx = element->x + x;
		while (y <= element->anim->frame.height)
		{
			bgy = element->y + y;
			index = (bgy * data->display.ptr1.ll)
					+ (bgx * (data->display.ptr1.bpp / 8));
			color = get_pixel_color((&element->anim->frame),
					y / element->scale_y, x / element->scale_x);
			if (color != 0 && (color & 0x00FFFFFF) != 0x00000000)
				*(unsigned int *)(data->display.ptr1.addr + index) = color;
			y++;
		}
		x++;
	}
}

void	put_button(t_data *data, t_anim *element, int flag)
{
	add_to_background(data, element);
	element->animspeed += data->player.frame * 70;
	if ((data->menu.state_menu == RESUME && flag == RESUME_ANIMATION)
		|| (data->menu.state_menu == SETTING && flag == SETTING_ANIMATION)
		|| (data->menu.state_menu == EXIT && flag == EXIT_ANIMATION))
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
	while (x < data->win_width)
	{
		y = 0;
		bgx = (x * element->anim->frame.width) / data->win_width;
		while (y <= data->win_height)
		{
			bgy = (y * element->anim->frame.height)  / data->win_height;
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
	put_background(data, &data->menu.background);
	put_button(data, &data->menu.resume, RESUME_ANIMATION);
	put_button(data, &data->menu.setting, SETTING_ANIMATION);
	put_button(data, &data->menu.exit, EXIT_ANIMATION);
	add_to_background(data, &data->menu.icone);
	update_frame(data, &data->menu.icone, 10);
	destroy_img(data, data->menu.background.x, data->menu.background.y);
	if (data->menu.background.y > 0)
		data->menu.background.y -= data->win_height * 0.05;
	update_frame_data(data);
}

void	put_color_cursor(t_data *data, int basex, int basey, t_color cursor)
{
	data->menu.setting_menu.barre.x = data->menu.setting_menu.speed.x 
	+ basex;
	data->menu.setting_menu.barre.y = basey;
	put_button(data, &data->menu.setting_menu.barre, RESUME_ANIMATION);
	data->menu.setting_menu.cursor.x = cursor.r 
	+ data->menu.setting_menu.barre.x 
	- (data->menu.setting_menu.barre.anim->frame.width * 0.5 * data->menu.setting_menu.barre.scale_x)
	 - (30 * data->menu.setting_menu.cursor.scale_x);
	data->menu.setting_menu.cursor.y = data->menu.setting_menu.barre.y;
	put_button(data, &data->menu.setting_menu.cursor, RESUME_ANIMATION);
	data->menu.setting_menu.barre.y = data->menu.setting_menu.barre.y + data->win_width * 0.05;
	put_button(data, &data->menu.setting_menu.barre, RESUME_ANIMATION);
	data->menu.setting_menu.cursor.x = cursor.g 
	+ data->menu.setting_menu.barre.x 
	- (data->menu.setting_menu.barre.anim->frame.width * 0.5 * data->menu.setting_menu.barre.scale_x)
	 - (30 * data->menu.setting_menu.cursor.scale_x);
	data->menu.setting_menu.cursor.y = data->menu.setting_menu.barre.y;
	put_button(data, &data->menu.setting_menu.cursor, RESUME_ANIMATION);
	data->menu.setting_menu.barre.y = data->menu.setting_menu.barre.y + data->win_width * 0.05;
	put_button(data, &data->menu.setting_menu.barre, RESUME_ANIMATION);
	data->menu.setting_menu.cursor.x = cursor.b
	+ data->menu.setting_menu.barre.x 
	- (data->menu.setting_menu.barre.anim->frame.width * 0.5 * data->menu.setting_menu.barre.scale_x)
	 - (30 * data->menu.setting_menu.cursor.scale_x);
	data->menu.setting_menu.cursor.y = data->menu.setting_menu.barre.y;
	put_button(data, &data->menu.setting_menu.cursor, RESUME_ANIMATION);
}
void 	put_cursor(t_data *data, int basex, int basey, int cursor)
{
	data->menu.setting_menu.barre.x = basex;
	data->menu.setting_menu.barre.y = basey;
	put_button(data, &data->menu.setting_menu.barre, RESUME_ANIMATION);
	data->menu.setting_menu.cursor.x = cursor +
	+ data->menu.setting_menu.barre.x 
	- (data->menu.setting_menu.barre.anim->frame.width * 0.5 * data->menu.setting_menu.barre.scale_x)
	+ (50 * data->menu.setting_menu.cursor.scale_x);
	data->menu.setting_menu.cursor.y = basey;
	put_button(data, &data->menu.setting_menu.cursor, RESUME_ANIMATION);

}
void	add_color_setting(t_data *data, int basex, int basey, unsigned int color)
{
	int	x = 0;
	int	y = 0;
	while (x < data->win_width * 0.05)
	{
		y = 0;
		while(y <  data->win_width * 0.05)
		{
			my_mlx_pixel_put(&data->display.ptr1, x + basex, y + basey, color);
			y++;
		}
		x++;
	}
	if (color == data->sprites.ceiling)
		put_color_cursor(data, basex, basey + y, data->menu.setting_menu.cursor_sky);
	else 
		put_color_cursor(data, basex, basey + y, data->menu.setting_menu.cursor_floor);
}

void	setting_menu(t_data *data)
{
	init_img(data);
	put_background(data, &data->menu.background);
	put_button(data, &data->menu.setting_menu.speed, RESUME_ANIMATION);
	put_cursor(data, data->menu.setting_menu.speed.x 
	+ (data->menu.setting_menu.speed.anim->frame.width * data->menu.setting_menu.speed.scale_x), data->menu.setting_menu.speed.y,
	data->menu.setting_menu.cursor_speed  * data->menu.setting_menu.barre.scale_x);
	put_button(data, &data->menu.setting_menu.cam, RESUME_ANIMATION);
	put_cursor(data, data->menu.setting_menu.cam.x
	+ (data->menu.setting_menu.cam.anim->frame.width * data->menu.setting_menu.cam.scale_x), data->menu.setting_menu.cam.y, 
	data->menu.setting_menu.cursor_cam *  data->menu.setting_menu.barre.scale_x);
	put_button(data, &data->menu.setting_menu.color, RESUME_ANIMATION);
	int	basey = data->menu.setting_menu.color.y + data->win_height * 0.1;
	add_color_setting(data, data->menu.setting_menu.color.x + data->win_width * 0.01
	, basey, data->sprites.ceiling);
	add_color_setting(data, data->menu.setting_menu.color.x 
	+ data->menu.setting_menu.color.anim->frame.height * data->menu.setting_menu.color.scale_x,
	basey, data->sprites.floor);
	update_frame(data, &data->menu.icone, 15);
	destroy_img(data, data->menu.background.x, data->menu.background.y);
	if (data->menu.background.y > 0)
		data->menu.background.y -= data->win_height * 0.05;
}
