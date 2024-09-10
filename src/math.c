/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: endoliam <endoliam@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 18:53:38 by endoliam          #+#    #+#             */
/*   Updated: 2024/09/10 22:45:47 by endoliam         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <X11/keysym.h>
#include <string.h>

#define mapWidth 24
#define mapHeight 24
#define screenWidth 640
#define screenHeight 480

int map[mapWidth][mapHeight]=
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

void	my_mlx_pixel_put(t_img *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bpp / 8));
	*(unsigned int*)dst = color;
}
void	ticktock(double *ticktock)
{
	(*ticktock)++;
}

void	update_frame_data(t_data *data)
{
	data->player.old_time = data->player.time;
	data->player.time = data->player.ticktock * 10;
	data->player.frame = (data->player.time - data->player.old_time) / 1000;
	data->player.movespeed = data->player.frame * 0.05;
	data->player.rotspeed = data->player.frame * 0.03;
	printf("FPS : %f\nmovespeed : %f\nrotspeed : %f\n", data->player.frame, data->player.movespeed, data->player.rotspeed);
}
void	init_img(t_data *data, int *ptr)
{
	if (data->display.ptr1.img)
	{
		data->display.ptr2.img = mlx_new_image(data->mlx, 800, 800);
		data->display.ptr2.addr = mlx_get_data_addr(data->display.ptr2.img, &data->display.ptr2.bpp, &data->display.ptr2.line_length,
								&data->display.ptr2.endian);
		(*ptr) = 2;
	}
	else
	{
		
		data->display.ptr1.img = mlx_new_image(data->mlx, 800, 800);
		data->display.ptr1.addr = mlx_get_data_addr(data->display.ptr1.img, &data->display.ptr1.bpp, &data->display.ptr1.line_length,
								&data->display.ptr1.endian);
		(*ptr) = 1;
	}
}

void	destroy_img(t_data *data, int *ptr)
{
	if ((*ptr) == 1)
	{
		mlx_put_image_to_window(data->mlx, data->win, data->display.ptr1.img, 0, 0);
		if (data && data->display.ptr2.img)
			mlx_destroy_image(data->mlx, data->display.ptr2.img);
		data->display.ptr2.img = NULL;
	}
	else if ((*ptr) == 2)
	{
		mlx_put_image_to_window(data->mlx, data->win, data->display.ptr2.img, 0, 0);
		if (data && data->display.ptr1.img)
			mlx_destroy_image(data->mlx, data->display.ptr1.img);
		data->display.ptr1.img = NULL;
	}
}
void	retracing(t_data *data)
{
	t_raycast	ray;
	memset(&ray, 0, sizeof(t_raycast));
	int			w = 800;
	int			h = 800;
	unsigned int 	color = 0;
	unsigned int 	blue = 0x004c51a7;
	unsigned int  	green = 0x0093db8a;
	unsigned int 	pink = 0x00cc3dd6;
	unsigned int 	red = 0x00d63d3d;
	unsigned int 	yellow = 0x00dfd565;
/*				ray casting 		*/
	int		x = 0;
	int		ptr = 0;
	int hit;
	int side;
	init_img(data, &ptr);
	while(x < w)
	{
		ticktock(&data->player.ticktock);
		ray.camx = 2 * x / (double)w - 1;
		ray.raydirx = data->player.dirx + data->player.planex * ray.camx;
		ray.raydiry = data->player.diry + data->player.planey * ray.camx;
/*				for DDA algo (find wich pos in map the line will be hit)      */
		ray.mapx = (int)data->player.posx; //current pos of in the map
		ray.mapy = (int)data->player.posy;
		// distance the ray has to travel from actual x vers next x anc actual y vers next y
		if (ray.raydirx == 0)
			ray.deltadistx = 1e30;
		else
			ray.deltadistx = fabs(1 / ray.raydirx);
		if (ray.raydiry == 0)
			ray.deltadisty = 1e30;
		else
			ray.deltadisty = fabs(1 / ray.raydiry);
		hit = 0; //for wall
		if (ray.raydirx < 0)
		{
			ray.stepx = -1;
			ray.sidedistx = (data->player.posx - ray.mapx) * ray.deltadistx;
		}
		else
		{
			ray.stepx = 1;
			ray.sidedistx = (ray.mapx + 1 - data->player.posx) * ray.deltadistx;
		}
		if (ray.raydiry < 0)
		{
			ray.stepy = -1;
			ray.sidedisty = (data->player.posy - ray.mapy) * ray.deltadisty;
		}
		else
		{
			ray.stepy = 1;
			ray.sidedisty = (ray.mapy + 1 - data->player.posy) * ray.deltadisty;
		}
		while (hit == 0)
		{
			if (ray.sidedistx < ray.sidedisty)
			{
				ray.sidedistx += ray.deltadistx;
				ray.mapx += ray.stepx;
				side = 0;
			}
			else
			{
				ray.sidedisty += ray.deltadisty;
				ray.mapy += ray.stepy;
				side = 1;
			}
			if (map[ray.mapx][ray.mapy] > 0)
				hit = 1;
		}
		if (side == 0)
			ray.perpwalldist = (ray.sidedistx - ray.deltadistx);
		else
			ray.perpwalldist = (ray.sidedisty - ray.deltadisty);
		ray.lineheight = (int)(h / ray.perpwalldist);
		ray.drawstart = ((ray.lineheight / 2) * -1) + h / 2;
		if (ray.drawstart < 0)
			ray.drawstart = 0;
		ray.drawend = ray.lineheight / 2 + h / 2;
		if (ray.drawend >= h)
			ray.drawend = h - 1;
		if (map[ray.mapx][ray.mapy] == 1)
			color = blue;
		else if (map[ray.mapx][ray.mapy] == 2)
			color = green;
		else if (map[ray.mapx][ray.mapy] == 3)
			color = pink;
		else if (map[ray.mapx][ray.mapy] == 4)
			color = red;
		else
			color = yellow;
		int		i = ray.drawstart;
		if (ptr == 1)
		{
			while (i <= ray.drawend)
			{
				my_mlx_pixel_put(&data->display.ptr1, x, i, color);
				i++;
			}
		}
		else
		{
			while (i <= ray.drawend)
			{
				my_mlx_pixel_put(&data->display.ptr2, x, i, color);
				i++;
			}
		}
		x++;
	}
	destroy_img(data, &ptr);
	//update_frame_data(game);
	data->player.old_time = data->player.time;
	data->player.time = data->player.ticktock * 10;
	data->player.frame = (data->player.time - data->player.old_time) / 1000;
	//printf("FPS : %f\nmovespeed : %f\nrotspeed : %f\n", data->player.frame, data->player.movespeed, data->player.rotspeed);
}

int	move(t_data *data)
{
	double		newx;
	double		newy;

	if (data->key.z)
	{
		newx = data->player.posx + data->player.dirx * data->player.movespeed;
		newy = data->player.posy + data->player.diry * data->player.movespeed;
		if (map[(int)(newx)][(int)(data->player.posy)] == 0)
			data->player.posx = newx;
		if (map[(int)(data->player.posx)][(int)(newy)] == 0)
			data->player.posy = newy;
	}
	if (data->key.s)
	{
		newx = data->player.posx - data->player.dirx * data->player.movespeed;
		newy = data->player.posy - data->player.diry * data->player.movespeed;
		if (map[(int)(newx)][(int)(data->player.posy)] == 0)
			data->player.posx = newx;
		if (map[(int)(data->player.posx)][(int)(newy)] == 0)
			data->player.posy = newy;
	}
	if (data->key.q)
	{
		newx = data->player.posx + data->player.diry * data->player.movespeed;
		newy = data->player.posy + data->player.dirx * data->player.movespeed;
		if (map[(int)(newx)][(int)(data->player.posy)] == 0)
			data->player.posx = newx;
		if (map[(int)(data->player.posx)][(int)(newy)] == 0)
			data->player.posy = newy;
	}
	if (data->key.d)
	{
		newx = data->player.posx - data->player.diry * data->player.movespeed;;
		newy = data->player.posy - data->player.dirx * data->player.movespeed;
		if (map[(int)(newx)][(int)(data->player.posy)] == 0)
			data->player.posx = newx;
		if (map[(int)(data->player.posx)][(int)(newy)] == 0)
			data->player.posy = newy;
	}
	if (data->key.right) 
	{
		double oldDirX = data->player.dirx;
		data->player.dirx = data->player.dirx * cos(-data->player.rotspeed) - data->player.diry * sin(-data->player.rotspeed);
		data->player.diry = oldDirX * sin(-data->player.rotspeed) + data->player.diry * cos(-data->player.rotspeed);
		double oldPlaneX = data->player.planex;
		data->player.planex = data->player.planex * cos(-data->player.rotspeed) - data->player.planey * sin(-data->player.rotspeed);
		data->player.planey = oldPlaneX * sin(-data->player.rotspeed) + data->player.planey * cos(-data->player.rotspeed);
	}
	if (data->key.left) 
	{
		double oldDirX = data->player.dirx;
		data->player.dirx = data->player.dirx * cos(data->player.rotspeed) - data->player.diry * sin(data->player.rotspeed);
		data->player.diry = oldDirX * sin(data->player.rotspeed) + data->player.diry * cos(data->player.rotspeed);
		double oldPlaneX = data->player.planex;
		data->player.planex = data->player.planex * cos(data->player.rotspeed) - data->player.planey * sin(data->player.rotspeed);
		data->player.planey = oldPlaneX * sin(data->player.rotspeed) + data->player.planey * cos(data->player.rotspeed);
	}
	retracing(data);
	return (0);
}
void	init_game(t_data *data)
{
	/* the inital value for calculate racasting */ 
	data->player.posx = 22; // vecteur du player (pos sur la map)
	data->player.posy = 11.5;
	data->player.dirx = -1; // vecteur direction du player (direction de depard n,s,e,w)
	data->player.diry = 0;
	data->player.planex = 0;	// niveau de la camera (angle)
	data->player.planey = 0.66;
	data->player.time = 0; // current frame
	data->player.old_time = 0; // old frame
	data->player.frame = 0;
	data->player.movespeed = 0.2;
	data->player.rotspeed = 0.03;
	data->display.ptr1.img = NULL;
	data->display.ptr2.img = NULL;
	retracing(data);
}