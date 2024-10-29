/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pause_menu_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: endoliam <endoliam@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 21:03:20 by endoliam          #+#    #+#             */
/*   Updated: 2024/10/29 16:00:25 by endoliam         ###   ########lyon.fr   */
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

void	add_to_background(t_data *data, t_anim element)
{
	int				x;
	int				y;
	int				bgx;
	int				bgy;
	unsigned int	color;
	int				index;

	x = 0;
	while(x <= element.anim->frame.width)
	{
		y = 0;
		bgx = element.x + x;
		while (y <= element.anim->frame.height)
		{
			bgy = element.y + y;
			index = (bgy * data->display.ptr1.ll) + (bgx * (data->display.ptr1.bpp / 8));
			color = get_pixel_color((&element.anim->frame), y / element.scale_y, x / element.scale_x);
			if (color != 0 && (color & 0x00FFFFFF) != 0x00000000)
				*(unsigned int *)(data->display.ptr1.addr + index) = color;
			y++;
		}
		x++;
	}
}

void	put_button(t_data *data, t_anim *element, int flag)
{
	add_to_background(data, *element);
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
		data->menu.icone.x = element->x - (element->anim->frame.width * element->scale_x);
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
	int				x = 0;
	int				y = 0;
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
			color = *(int *)(element->anim->frame.addr + (element->anim->frame.ll * bgy) + (bgx * element->anim->frame.bpp / 8));
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
	add_to_background(data, *&data->menu.icone);
	update_frame(data, &data->menu.icone, 15);
	destroy_img(data, data->menu.background.x, data->menu.background.y);
	if (data->menu.background.y > 0)
		data->menu.background.y -= data->player.frame * 7000;
	update_frame_data(data);
}

void adapt_color(unsigned int original_color, unsigned int target_color, unsigned int *result_color) 
{
    int r_orig = (original_color >> 16) & 0xFF;
    int g_orig = (original_color >> 8) & 0xFF;
    int b_orig = original_color & 0xFF;
    int brightness_orig = (r_orig * 299 + g_orig * 587 + b_orig * 114) / 1000;
    int r_target = (target_color >> 16) & 0xFF;
    int g_target = (target_color >> 8) & 0xFF;
    int b_target = target_color & 0xFF;
    float factor = (brightness_orig / 255.0) * 5;
    r_target = (int)(r_target * ( factor));
    g_target = (int)(g_target * ( factor));
    b_target = (int)(b_target * ( factor));
    r_target = r_target < 0 ? 0 : r_target > 255 ? 255 : r_target;
    g_target = g_target < 0 ? 0 : g_target > 255 ? 255 : g_target;
    b_target = b_target < 0 ? 0 : b_target > 255 ? 255 : b_target;
    *result_color = (r_target << 16) | (g_target << 8) | b_target;
}

void	set_sky(t_data *data, t_raycast *ray, int x, int y)
{
	int			hit;
	t_raycast	sky_ray;

	hit = 0;
	sky_ray.sidedistx = ray->sidedistx;
	sky_ray.sidedisty = ray->sidedisty;
	sky_ray.deltadistx = ray->deltadistx;
	sky_ray.deltadisty = ray->deltadisty;
	sky_ray.raydirx = ray->raydirx;
	sky_ray.raydiry = ray->raydiry;
	if (ray->sidedistx < ray->sidedisty)
		sky_ray.perpwalldist = (sky_ray.sidedistx - sky_ray.deltadistx) * 6;
	else
		sky_ray.perpwalldist = (sky_ray.sidedisty - sky_ray.deltadisty) * 6;
	sky_ray.lineheight = (int)((data->win_height * 0.5));
	sky_ray.linestart = sky_ray.lineheight;
	int		texx, texy;
	double	hity;
	if (sky_ray.raydirx < 0)
		hity = (data->player.posy + sky_ray.perpwalldist * sky_ray.raydiry);
	else 
		hity = (data->player.posy - sky_ray.perpwalldist * sky_ray.raydiry);
	hity -= floor(hity);
	double ray_angle = atan2(sky_ray.raydiry, sky_ray.raydirx);
	texx = (int)((ray_angle / (2.0 * M_PI)) * (data->menu.background.anim->frame.width));
	if (texx < 0)
		texx += (data->menu.background.anim->frame.width);
	texy = (int)(hity * (data->menu.background.anim->frame.height * 0.5));
	texy = (int)((data->player.horizon + (y - sky_ray.lineheight)) * (data->menu.background.anim->frame.height * 0.5) / data->win_height);
	if (texy < 0)
		texy *= -1;
	texy = abs(texy);
	unsigned int color = *(int *)(data->menu.background.anim->frame.addr + (data->menu.background.anim->frame.ll * texy) + (texx * data->menu.background.anim->frame.bpp / 8));
	int		r = (color >> 16) & 0xFF;
	int		g = (color >> 8) & 0xFF;
	int		b = color & 0xFF;
	if ((r <= 255 && r >= 33) || (g <= 110 && g >= 20) || (b <= 219 && b >= 68))
	{
		unsigned int adapted_color;
    	adapt_color(color, data->sprites.ceiling, &adapted_color);
		color = adapted_color;
	}
	if (color != 0)
		my_mlx_pixel_put(&data->display.ptr1, x, y, color);
}
