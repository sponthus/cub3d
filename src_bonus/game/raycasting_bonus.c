/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sponthus <sponthus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 18:53:38 by endoliam          #+#    #+#             */
/*   Updated: 2024/10/30 12:48:31 by sponthus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	set_drawline(t_data *data, t_raycast *ray, int side)
{
	if (side == 0)
		ray->perpwalldist = (ray->sidedistx - ray->deltadistx) * 6;
	else
		ray->perpwalldist = (ray->sidedisty - ray->deltadisty) * 6;
	data->player.horizon = data->player.pitch * data->win_height;
	ray->lineheight = (int)((data->win_height * data->player.wallheight)
			/ ray->perpwalldist);
	ray->drawstart = (((ray->lineheight * 0.5) * -1) + (data->win_height * 0.5))
		- data->player.horizon ;
	ray->drawstart -= data->player.posz;
	ray->linestart = ray->drawstart;
	if (ray->drawstart < 0)
		ray->drawstart = 0;
	ray->drawend = (ray->lineheight * 0.5 + (data->win_height * 0.5))
		- data->player.horizon;
	ray->drawend -= data->player.posz;
	if (ray->drawend >= data->win_height)
		ray->drawend = data->win_height - 1;
}

void	find_hit_point(t_data *data, t_raycast *ray, int *side)
{
	ray->door = 0;
	while (42)
	{
		if (ray->sidedistx < ray->sidedisty)
		{
			ray->sidedistx += ray->deltadistx;
			ray->mapx += ray->stepx;
			(*side) = 0;
		}
		else
		{
			ray->sidedisty += ray->deltadisty;
			ray->mapy += ray->stepy;
			(*side) = 1;
		}
		if (data->map[ray->mapx][ray->mapy]
			&& data->map[ray->mapx][ray->mapy] != '0')
		{
			if (data->map[ray->mapx][ray->mapy] == 'D')
				ray->door = 1;
			if (data->map[ray->mapx][ray->mapy] != 'O')
				break ;
		}
	}
}

void	dda_algorithme(t_data *data, t_raycast *ray)
{
	if (ray->raydirx != 0)
		ray->deltadistx = fabs(1 / ray->raydirx);
	if (ray->raydiry != 0)
		ray->deltadisty = fabs(1 / ray->raydiry);
	if (ray->raydirx < 0)
	{
		ray->stepx = -1;
		ray->sidedistx = (data->player.posx - ray->mapx) * ray->deltadistx;
	}
	else
		ray->sidedistx = (ray->mapx + 1 - data->player.posx) * ray->deltadistx;
	if (ray->raydiry < 0)
	{
		ray->stepy = -1;
		ray->sidedisty = (data->player.posy - ray->mapy) * ray->deltadisty;
	}
	else
		ray->sidedisty = (ray->mapy + 1 - data->player.posy) * ray->deltadisty;
}

void	init_raycast(t_data *data, t_raycast *ray, int x)
{
	ray->camx = 2 * x / (double)data->win_width - 1;
	ray->raydirx = data->player.dirx + data->player.planex * ray->camx;
	ray->raydiry = data->player.diry + data->player.planey * ray->camx;
	ray->mapx = (int)data->player.posx;
	ray->mapy = (int)data->player.posy;
	ray->deltadistx = 1e30;
	ray->deltadisty = 1e30;
	ray->stepy = 1;
	ray->stepx = 1;
}

void	raycasting(t_data *data)
{
	t_raycast	ray;
	int			x;
	int			side;

	init_img(data);
	x = 0;
	side = 0;
	ft_memset(&ray, 0, sizeof(t_raycast));
	while (x < data->win_width)
	{
		init_raycast(data, &ray, x);
		dda_algorithme(data, &ray);
		find_hit_point(data, &ray, &side);
		set_drawline(data, &ray, side);
		draw_line(data, &ray, x, side);
		x++;
	}
	draw_minimap(data);
	destroy_img(data, 0, 0);
	update_frame_data(data);
	update_frame(data, &data->menu.background, 30);
}
