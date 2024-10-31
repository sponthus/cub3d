/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sponthus <sponthus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 13:06:52 by endoliam          #+#    #+#             */
/*   Updated: 2024/10/31 12:34:54 by sponthus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	calc_texx_x(t_data *data, t_raycast *ray)
{
	double	hitx;
	int		texx;

	texx = 0;
	hitx = (data->player.posx + (ray->perpwalldist / 6) * ray->raydirx);
	hitx -= floor(hitx);
	if (ray->dir == WEST)
	{
		texx = (int)((hitx) * (double)(data->sprites.we.width));
	}
	if (ray->dir == EAST)
	{
		texx = (int)((hitx) * (double)(data->sprites.ea.width));
	}
	return (texx);
}

int	calc_texx_y(t_data *data, t_raycast *ray)
{
	double	hitx;
	int		texx;

	texx = 0;
	hitx = (data->player.posy + (ray->perpwalldist / 6) * ray->raydiry);
	hitx -= floor(hitx);
	if (ray->dir == NORTH)
	{
		texx = (int)((hitx) * (double)(data->sprites.no.width));
	}
	else if (ray->dir == SOUTH)
	{
		texx = (int)((hitx) * (double)(data->sprites.so.width));
	}
	return (texx);
}

int	tex_find_color(t_img *img, int y, int x)
{
	int	pixy;

	pixy = (y * img->height) * 0.01;
	if (x >= 0 && x < img->width && pixy >= 0 && pixy < img->height)
		return (*(int *)(img->addr + (img->ll * pixy) + (x * img->bpp / 8)));
	return (0x0);
}

int	tex_chose_color(t_data *data, int x, int y, int dir)
{
	if (dir == NORTH)
		return (tex_find_color(&data->sprites.no, x, y));
	else if (dir == SOUTH)
		return (tex_find_color(&data->sprites.so, x, y));
	else if (dir == WEST)
		return (tex_find_color(&data->sprites.we, x, y));
	else if (dir == EAST)
		return (tex_find_color(&data->sprites.ea, x, y));
	return (0x0);
}

int	chose_dir(int side, t_raycast *ray)
{
	if (side == 0)
	{
		if (ray->stepx < 0)
			return (NORTH);
		else
			return (SOUTH);
	}
	else
	{
		if (ray->stepy < 0)
			return (WEST);
		else
			return (EAST);
	}
}
