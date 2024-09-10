/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: endoliam <endoliam@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 18:53:38 by endoliam          #+#    #+#             */
/*   Updated: 2024/09/10 12:49:39 by endoliam         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "cub3d.h"
#include "raycast.h"
#include <X11/keysym.h>

#define mapWidth 24
#define mapHeight 24
#define screenWidth 640
#define screenHeight 480

int worldMap[mapWidth][mapHeight]=
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

int	retracing(t_data data, int keycode)
{
	
	int		w = 800;
	int		h = 800;
/* the inital value for calculate racasting */ 
	double		posx = 10; // vecteur du player (pos sur la map)
	double		posy = 20;
	double		dirx = -1; // vecteur direction du player (direction de depard n,s,e,w)
	double		diry = 0;
	double		planex = 0;	// niveau de la camera (angle)
	double		planey = 0.90;
	double		time = 0; // current frame
	double		old_time = 0; // old frame
	double		frame = 0;
/*				ray casting 		*/
	double		camx;	// coordonener du niveau de la camera (gauche -1 droit 1 centre 0)
	double		raydirx; // rayon  de la camera
	double		raydiry;

	int		x = 0;
	t_img	img;

	
	img.img = mlx_new_image(data.mlx, w, h);
	img.addr = mlx_get_data_addr(img.img, &img.bpp, &img.line_length,
								&img.endian);
	
	
	while(x < w)
	{
		simulateTick();
		camx = 2 * x / (double)w - 1;
		raydirx = dirx + planex * camx;
		raydiry = diry + planey * camx;
/*				for DDA algo (find wich pos in map the line will be hit)      */
		int			mapx = (int)posx; //current pos of in the map
		int			mapy = (int)posy;
		double		sidedistx; // distance du rayon from his start position to the first side x or y
		double		sidedisty;
		double		deltadistx; // distance the ray has to travel from actual x vers next x anc actual y vers next y
		if (raydirx == 0)
			deltadistx = 1e30;
		else
			deltadistx = fabs(1 / raydirx);
		double		deltadisty;
		if (raydiry == 0)
			deltadisty = 1e30;
		else
			deltadisty = fabs(1 / raydiry);
		
	
		int			stepx; // index direction
		int			stepy;
	
		int			hit = 0; //for wall
		int			side;
	
		if (raydirx < 0)
		{
			stepx = -1;
			sidedistx = (posx - mapx) * deltadistx;
		}
		else
		{
			stepx = 1;
			sidedistx = (mapx + 1 - posx) * deltadistx;
		}
		if (raydiry < 0)
		{
			stepy = -1;
			sidedisty = (posy - mapy) * deltadisty;
		}
		else
		{
			stepy = 1;
			sidedisty = (mapy + 1 - posy) * deltadisty;
		}
		while (hit == 0)
		{
			if (sidedistx < sidedisty)
			{
				sidedistx += deltadistx;
				mapx += stepx;
				side = 0;
			}
			else
			{
				sidedisty += deltadisty;
				mapy += stepy;
				side = 1;
			}
			if (worldMap[mapx][mapy] > 0)
				hit = 1;
		}
		double		perpwalldist; // distance du rayon
		if (side == 0)
			perpwalldist = (sidedistx - deltadistx);
		else
			perpwalldist = (sidedisty - deltadisty);
		int		lineheight;

		lineheight = (int)(h / perpwalldist);
		int 	drawstart = ((lineheight / 2) * -1) + h / 2;
		if (drawstart < 0)
			drawstart = 0;
		int		drawend = lineheight / 2 + h / 2;
		if (drawend >= h)
			drawend = h - 1; 
		unsigned int 	color = 0;

		unsigned int 	blue = 0x004c51a7;
		unsigned int  	green = 0x0093db8a;
		unsigned int 	pink = 0x00cc3dd6;
		unsigned int 	red = 0x00d63d3d;
		unsigned int 	yellow = 0x00dfd565;
	
		if (worldMap[mapx][mapy] == 1)
			color = blue;
		else if (worldMap[mapx][mapy] == 2)
			color = green;
		else if (worldMap[mapx][mapy] == 3)
			color = pink;
		else if (worldMap[mapx][mapy] == 4)
			color = red;
		else
			color = yellow;
		int		i = drawstart;
		while (i <= drawend)
		{
			my_mlx_pixel_put(&img, x, i, color);
			i++;
		}
		x++;
		
	}
	mlx_put_image_to_window(data.mlx, data.win, img.img, 0, 0);
	old_time = time;
	time = getTicks();
	frame = (time - old_time) / 1000;
	double movespeed = frame * 5.0;
	double rotspeed = frame * 3;
	printf("FPS : %f\nmovespeed : %f\nrotspeed : %f\n", frame, movespeed, rotspeed);
	(void)keycode;
	return (0);	
}