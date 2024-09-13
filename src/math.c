/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: endoliam <endoliam@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 18:53:38 by endoliam          #+#    #+#             */
/*   Updated: 2024/09/13 19:08:57 by endoliam         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <X11/keysym.h>
#include <string.h>
#include <sys/time.h>

int map[24][24]=
{
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};



void	update_frame_data(t_data *data)
{
	data->player.old_time = data->player.time;
	data->player.time = data->player.ticktock * 10;
	data->player.frame = (data->player.time - data->player.old_time)/1000;
	data->player.movespeed = data->player.frame * 0.005;
	data->player.rotspeed = data->player.frame * 0.003;
}
void	set_drawline(t_data *data ,t_raycast *ray, int side)
{
	if (side == 0)
		ray->perpwalldist = (ray->sidedistx - ray->deltadistx);
	else
		ray->perpwalldist = (ray->sidedisty - ray->deltadisty);
	data->player.horizon = data->player.pitch * data->win_height;
	ray->lineheight = (int)((data->win_height * data->player.wallheight) / ray->perpwalldist);
	ray->drawstart = (((ray->lineheight / 2) * -1) + (data->win_height / 2)) - data->player.horizon ;
	ray->drawstart -=  data->player.posz;
	if (ray->drawstart < 0)
		ray->drawstart = 0;
	ray->drawend = (ray->lineheight / 2 + (data->win_height / 2)) - data->player.horizon;
	ray->drawend -=  data->player.posz; 
	if (ray->drawend >= data->win_height)
		ray->drawend = data->win_height - 1;
}
void	find_hit_point(t_raycast *ray, int *side)
{
	int 	hit;

	hit = 0;
	while (hit == 0)
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
		if (map[ray->mapx][ray->mapy] > 0)
			hit = 1;
	}
}
void	draw_line(t_data *data, t_raycast *ray, int x, int ptr, int side)
{
	/*					set color 			*/
	unsigned int 	color = 0;
	unsigned int 	blue = 0x004c51a7;
	unsigned int  	green = 0x0093db8a;
	unsigned int 	pink = 0x00cc3dd6;
	unsigned int 	red = 0x00bd1155;
	unsigned int 	yellow = 0x00dfd565;
	if (map[ray->mapx][ray->mapy] == 1)
		color = blue;
	else if (map[ray->mapx][ray->mapy] == 2)
		color = green;
	else if (map[ray->mapx][ray->mapy] == 3)
		color = pink;
	else if (map[ray->mapx][ray->mapy] == 4)
		color = red;
	else
		color = yellow;
	if (side == 1)
		color = color / 2;
	color = calculate_shaded_color(color, ray->perpwalldist);
	/*					draw_line			*/
	if (ptr == 1)
	{
		while (ray->drawstart <= ray->drawend)
		{
			my_mlx_pixel_put(&data->display.ptr1, x, ray->drawstart, color);
			ray->drawstart++;
		}
	}
	else
	{
		while (ray->drawstart <= ray->drawend)
		{
			my_mlx_pixel_put(&data->display.ptr2, x, ray->drawstart, color);
			ray->drawstart++;
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
	ray->mapx = (int)data->player.posx; //current pos of in the map
	ray->mapy = (int)data->player.posy;
	ray->deltadistx = 1e30;
	ray->deltadisty = 1e30;
	ray->stepy = 1;
	ray->stepx = 1;
}
void	raycasting(t_data *data)
{
	t_raycast	ray;
	int			x = 0;
	int			ptr = 0;
	int			side = 0;

	init_img(data, &ptr);
	memset(&ray, 0, sizeof(t_raycast));
	while(x < data->win_width)
	{
		init_raycast(data, &ray, x);
		dda_algorithme(data, &ray);
		find_hit_point(&ray, &side);
		set_drawline(data, &ray, side);
		draw_line(data, &ray, x, ptr, side);
		x++;
	}
	destroy_img(data, &ptr);
	data->player.old_time = data->player.time;
	data->player.time = my_get_time();
	if (data->player.time != data->player.old_time)
		data->player.frame = (data->player.time - data->player.old_time) / 10000;
	else
		data->player.frame = 0;
	if (data->player.frame != 0)
	{
		data->player.speed = data->player.frame * 3;
		data->player.movespeed = data->player.speed;
		data->player.rotspeed = data->player.frame * 2;
		printf("FPS : %f\nmovespeed : %f\nrotspeed : %f\n", 1/data->player.frame, data->player.movespeed, data->player.rotspeed);
	}
}



void	init_game(t_data *data)
{
	/* the inital value for calculate racasting */ 
	data->player.posx = 22; // vecteur du player (pos sur la map)
	data->player.posy = 11.5;
	data->player.posz = 0;
	data->player.pitch = 0.0;
	data->player.dirx = -1; // vecteur direction du player (direction de depard n,s,e,w)
	data->player.diry = 0;
	data->player.planex = 0;	// niveau de la camera (angle)
	data->player.planey = 0.66;
	data->player.time = 0; // current frame
	data->player.old_time = 0; // old frame
	data->player.frame = 0;
	data->player.gravity = 0.05;
	data->player.speed = 0.02;
	data->player.movespeed = data->player.speed;
	data->player.rotspeed = 0.01;
	data->player.wallheight = 5;
	raycasting(data);
}

void	player_move(t_data *data, double dirx, double diry)
{
	double		newx;
	double		newy;

	newx = data->player.posx + dirx * data->player.movespeed;
	newy = data->player.posy + diry * data->player.movespeed;
	if (map[(int)(newx)][(int)(data->player.posy)] == 0)
		data->player.posx = newx;
	if (map[(int)(data->player.posx)][(int)(newy)] == 0)
		data->player.posy = newy;

}