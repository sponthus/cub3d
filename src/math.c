/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: endoliam <endoliam@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 18:53:38 by endoliam          #+#    #+#             */
/*   Updated: 2024/09/11 19:53:11 by endoliam         ###   ########lyon.fr   */
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

unsigned int calculate_shaded_color(unsigned int color, double distance)
{
    // Adjust shading factor (more subtle shading)
	double max_distance = 40.0; // Maximum distance for shading effect
	double shading_factor = 1.0 - fmin(distance / max_distance, 1.0); // Smoothly interpolate shading
	
	unsigned int r = (color >> 16) & 0xFF;
	unsigned int g = (color >> 8) & 0xFF;
	unsigned int b = color & 0xFF;

	// Apply shading with a lower intensity
	r = (unsigned int)(r * shading_factor);
	g = (unsigned int)(g * shading_factor);
	b = (unsigned int)(b * shading_factor);

	// Ensure color values are within the valid range [0, 255]
	if (r > 255) r = 255;
	if (g > 255) g = 255;
	if (b > 255) b = 255;
	
	return (r << 16) | (g << 8) | b;
}

void	put_pixel_background(t_data *data, t_img *dis)
{
	int		x = 0;
	int		y = 0;
	unsigned int color1 = 0x00f3aeae;
	unsigned int color2 = 0x00aef3da;
	double		up = 1;
	//if (data->player.up > 1.1)
	//	up = (data->player.up * 1.3);
	//else 
	up = (800 / 2.0) - (data->player.pitch * 800);// + data->player.posz * (800 / 2.0);
	if (data->player.posz > 0)
		up -= data->player.posz;
	else 
		up -= data->player.posz / 1.4;
	while (x < 800)
	{
		y = 0;
		while (y < 800)
		{
			if (y > up)
			{
				my_mlx_pixel_put(dis, x, y, color1);
			}
			else
			{
				my_mlx_pixel_put(dis, x, y, color2);
			}
			y++;
		}
		x++;
	}
}

void	display_background(t_data *data, t_img *img)
{
	put_pixel_background(data, img);
	
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
void	superposition_img(t_img *background, t_img *face)
{
	unsigned int	color = 0;
	int				x = 0;
	int				y = 0;
	int				index = 0;

	while (y < 800)
	{
       x = 0;
        while (x < 800)
		{
			index = y * background->line_length + x * (background->bpp / 8);
			color = *(unsigned int *)(face->addr + index);
			if (color != 0)
			    *(unsigned int *)(background->addr + index) = color;
			x++;
		}
		y++;
	}
}


void	init_img(t_data *data, int *ptr)
{
	if (data->display.ptr1.img)
	{
		data->display.bg2.img = mlx_new_image(data->mlx, 800, 800);
		data->display.bg2.addr = mlx_get_data_addr(data->display.bg2.img, &data->display.bg2.bpp, &data->display.bg2.line_length,
								&data->display.bg2.endian);
		put_pixel_background(data, &data->display.bg2);
		data->display.ptr2.img = mlx_new_image(data->mlx, 800, 800);
		data->display.ptr2.addr = mlx_get_data_addr(data->display.ptr2.img, &data->display.ptr2.bpp, &data->display.ptr2.line_length,
								&data->display.ptr2.endian);
		(*ptr) = 2;
	}
	else
	{
		data->display.bg1.img = mlx_new_image(data->mlx, 800, 800);
		data->display.bg1.addr = mlx_get_data_addr(data->display.bg1.img, &data->display.bg1.bpp, &data->display.bg1.line_length,
								&data->display.bg1.endian);
		put_pixel_background(data, &data->display.bg1);
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
		superposition_img(&data->display.bg1, &data->display.ptr1);
		mlx_put_image_to_window(data->mlx, data->win, data->display.bg1.img, 0, 0);
		if (data && data->display.bg2.img)
			mlx_destroy_image(data->mlx, data->display.bg2.img);
		if (data && data->display.ptr2.img)
			mlx_destroy_image(data->mlx, data->display.ptr2.img);
		data->display.ptr2.img = NULL;
	}
	else if ((*ptr) == 2)
	{
		superposition_img(&data->display.bg2, &data->display.ptr2);
		mlx_put_image_to_window(data->mlx, data->win, data->display.bg2.img, 0, 0);
		if (data && data->display.bg1.img)
			mlx_destroy_image(data->mlx, data->display.bg1.img);
		if (data && data->display.ptr1.img)
			mlx_destroy_image(data->mlx, data->display.ptr1.img);	
		data->display.ptr1.img = NULL;
	}
}

void	retracing(t_data *data)
{
	t_raycast	ray;
	memset(&ray, 0, sizeof(t_raycast));
	int				w = 800;
	int				h = 800;
	unsigned int 	color = 0;
	unsigned int 	blue = 0x004c51a7;
	unsigned int  	green = 0x0093db8a;
	unsigned int 	pink = 0x00cc3dd6;
	unsigned int 	red = 0x00bd1155;
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
		data->player.horizon = data->player.pitch * h;
		ray.lineheight = (int)((h * data->player.wallheight) / ray.perpwalldist);// * ((data->player.pitch + 1) * 0.5 + 0.5);
		ray.drawstart = (((ray.lineheight / 2) * -1) + (h / 2)) - data->player.horizon ;
		//ray.drawstart = (((ray.lineheight / 2) * -1) + (h * data->player.up) / 2) * data->player.up;
		//if (data->player.up < 1)
		//	ray.drawstart = (((ray.lineheight / 2) * -1) + (h * data->player.up ) / 2) * (data->player.up * 0.9);
		ray.drawstart -=  data->player.posz;
		if (ray.drawstart < 0)
			ray.drawstart = 0;
		
		//ray.drawend = ((ray.lineheight / 2 )+ (h * data->player.up)  / 2) * data->player.up;// + h * (1 - data->player.up) / 2;
		//if (data->player.up < 1)
		//	ray.drawend = (ray.lineheight / 2 + (h * data->player.up)  / 2) * (data->player.up * 0.5 + 0.5);
		ray.drawend = (ray.lineheight / 2 + (h / 2)) - data->player.horizon;
		ray.drawend -=  data->player.posz; 
		if (ray.drawend >= h)
			ray.drawend = h - 0.1;
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
		if (side == 1)
			color = color /2;
		color = calculate_shaded_color(color, ray.perpwalldist);
		int		i = ray.drawstart;
		if (ptr == 1)
		{
			while (i <= ray.drawend)
			{
				//color = color_custom *(x % 16 && i % 16);
				my_mlx_pixel_put(&data->display.ptr1, x, i, color);
				i++;
			}
		}
		else
		{
			while (i <= ray.drawend)
			{
				//color = color_custom * (x % 16 && i % 16);
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
void	jump(t_data *data)
{
	int		i = 0;
	while (i < 50)
	{
		data->player.posz -= 4;
		retracing(data);
		i += 4;
	}
	while (i >= 0)
	{
		data->player.posz += 4;
		retracing(data);
		i -= 4;
	}
	return ;
}
int	move(t_data *data)
{
	double		newx;
	double		newy;
	double		olddirx;
	double		oldplanex;

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
		newx = data->player.posx - data->player.diry * data->player.movespeed;
		newy = data->player.posy + data->player.dirx * data->player.movespeed;
		if (map[(int)(newx)][(int)(data->player.posy)] == 0)
			data->player.posx = newx;
		if (map[(int)(data->player.posx)][(int)(newy)] == 0)
			data->player.posy = newy;
	}
	if (data->key.d)
	{
		newx = data->player.posx + data->player.diry * data->player.movespeed;;
		newy = data->player.posy - data->player.dirx * data->player.movespeed;
		if (map[(int)(newx)][(int)(data->player.posy)] == 0)
			data->player.posx = newx;
		if (map[(int)(data->player.posx)][(int)(newy)] == 0)
			data->player.posy = newy;
	}
	if (data->key.right) 
	{
		olddirx = data->player.dirx;
		data->player.dirx = data->player.dirx * cos(-data->player.rotspeed) - data->player.diry * sin(-data->player.rotspeed);
		data->player.diry = olddirx * sin(-data->player.rotspeed) + data->player.diry * cos(-data->player.rotspeed);
		oldplanex = data->player.planex;
		data->player.planex = data->player.planex * cos(-data->player.rotspeed) - data->player.planey * sin(-data->player.rotspeed);
		data->player.planey = oldplanex * sin(-data->player.rotspeed) + data->player.planey * cos(-data->player.rotspeed);
	}
	if (data->key.left) 
	{
		olddirx = data->player.dirx;
		data->player.dirx = data->player.dirx * cos(data->player.rotspeed) - data->player.diry * sin(data->player.rotspeed);
		data->player.diry = olddirx * sin(data->player.rotspeed) + data->player.diry * cos(data->player.rotspeed);
		oldplanex = data->player.planex;
		data->player.planex = data->player.planex * cos(data->player.rotspeed) - data->player.planey * sin(data->player.rotspeed);
		data->player.planey = oldplanex * sin(data->player.rotspeed) + data->player.planey * cos(data->player.rotspeed);
	}
	if (data->key.up)
	{
		if (data->player.pitch > -0.7)
			data->player.pitch -= data->player.rotspeed;
	}
	if (data->key.down)
	{
		if (data->player.pitch < 0.8)
			data->player.pitch += data->player.rotspeed;	
	}
	if (data->key.tab && !data->key.c)
		data->player.movespeed = 0.3;
	else if (!data->key.tab && !data->key.c)
		data->player.movespeed = 0.2;
	if (data->key.space)
	{
		data->player.posz += data->player.jump_speed;
        data->player.jump_speed += data->player.gravity;
		if (data->player.posz >= data->player.initz)
		{
			data->player.posz = data->player.initz;
			data->key.space = 0;
			data->player.jump_speed  = 0;
		}
	}
	//data->player.wallheight += 0.002;
	retracing(data);
	return (0);
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
	data->player.gravity = 0.9;
	data->player.movespeed = 0.2;
	data->player.rotspeed = 0.08;
	data->player.wallheight = 5;
	retracing(data);
}