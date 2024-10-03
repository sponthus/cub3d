/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sponthus <sponthus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 18:53:38 by endoliam          #+#    #+#             */
/*   Updated: 2024/10/03 14:34:58 by sponthus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <X11/keysym.h>
#include <string.h>
#include <sys/time.h>


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
		ray->perpwalldist = (ray->sidedistx - ray->deltadistx) * 4;
	else
		ray->perpwalldist = (ray->sidedisty - ray->deltadisty) * 4;
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
void	find_hit_point(t_data *data, t_raycast *ray, int *side)
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
		if (data->map[ray->mapx][ray->mapy]
			&& data->map[ray->mapx][ray->mapy] > '0')
			hit = 1;
	}
}

// tex->width represente la largeur de la texturem idem height
// x et y representent en pixel la correspondance, de 0 a tex->width/height
// Donc pourcentage deja applique

int	find_color_in_tex(t_img *img, int y, int x)
{
	if (x >= 0 && x < img->width && y >= 0 && y < img->height)
		return (*(int *)(img->addr + (img->ll * y) + (x * img->bpp / 8)));
	return (0x0);
}

int	chose_color(t_data *data, int x, int y, int dir)
{
	if (dir == NORTH)
		return (find_color_in_tex(&data->sprites.no, x, y));
	else if (dir == SOUTH)
		return (find_color_in_tex(&data->sprites.so, x, y));
	else if (dir == WEST)
		return (find_color_in_tex(&data->sprites.we, x, y));
	else if (dir == EAST)
		return (find_color_in_tex(&data->sprites.ea, x, y));
	return (0x0);
}


void	draw_line(t_data *data, t_raycast *ray, int x, int side)
{
	/*					set color 			*/
	unsigned int 	color = 0;
	unsigned int 	blue = 0x004c51a7;
	unsigned int  	green = 0x0093db8a;
	unsigned int 	pink = 0x00cc3dd6;
	unsigned int 	red = 0x00bd1155;
	int				hitx = 0;
	int				dir = 0;

	if (side == 0 && ray->stepx < 0)
	{
		hitx = data->player.posx + ray->perpwalldist * ray->raydirx;
		dir = NORTH; // To check
		color = pink;
	}
	if (side == 0 && ray->stepx > 0)
	{
		hitx = data->player.posx + ray->perpwalldist * ray->raydirx;
		dir = SOUTH; // To check
		color = blue;
	}
	if (side == 1 && ray->stepy > 0)
	{
		hitx = data->player.posy + ray->perpwalldist * ray->raydiry;
		color = red;
		dir = WEST; // TO CHECK
	}
	else if (side == 1 && ray->stepy < 0)
	{
		hitx = data->player.posy + ray->perpwalldist * ray->raydiry;
		color = green;
		dir = EAST;
	}
	color = calculate_shaded_color(color, ray->perpwalldist);
	/*					draw_line			*/
	int		y = 0;
	// Reste a transformer x et y en hitx et hity 
	// Representant le pixel, de 0 a img->height/width
	// Donc pourcentage touche de la texture rapporte a img->height/width
	while (y <= data->win_height)
	{
		if (y >= ray->drawstart && y <= ray->drawend)
		{
			color = chose_color(data, x, y, dir);
			color = calculate_shaded_color(color, ray->perpwalldist);
			my_mlx_pixel_put(&data->display.ptr1, x, y, color);
		}
		else if (y < ray->drawstart)
			my_mlx_pixel_put(&data->display.ptr1, x, y, 0x00f3aeae);
		else if (y > ray->drawend)
			my_mlx_pixel_put(&data->display.ptr1, x, y, 0x00aef3da);
		y++;
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
	int			side = 0;

	init_img(data);
	ft_memset(&ray, 0, sizeof(t_raycast));
	while(x < data->win_width)
	{
		init_raycast(data, &ray, x);
		dda_algorithme(data, &ray);
		find_hit_point(data, &ray, &side);
		set_drawline(data, &ray, side);
		draw_line(data, &ray, x, side);
		x++;
	}
	destroy_img(data);
	data->player.old_time = data->player.time;
	data->player.time = my_get_time();
	if (data->player.time != data->player.old_time)
		data->player.frame = (data->player.time - data->player.old_time) / 10000;
	else
		data->player.frame = 0;
	if (data->player.frame != 0)
	{
		data->player.speed = data->player.frame * 0.9;
		if (data->key.tab)
			data->player.speed *= 2;
		data->player.movespeed = data->player.speed;
		data->player.rotspeed = data->player.frame * 0.7;
		//printf("FPS : %f\nmovespeed : %f\nrotspeed : %f\n", 1/data->player.frame, data->player.movespeed, data->player.rotspeed);
	}
}

bool	is_player_init_pos(char c, t_move *player)
{
	if (c == 'N')
	{
		player->dirx = -1;
		player->planey = player->fov / 90;
		return (true);
	}
	else if (c == 'S')
	{
		player->dirx = 1;
		player->planey = -player->fov / 90;
		return (true);
	}
	else if (c == 'E')
	{
		player->diry = 1;
		player->planex = player->fov / 90;
		return (true);
	}
	else if (c == 'W')
	{
		player->diry = -1;
		player->planex = -player->fov / 90;
		return (true);
	}
	return (false);
}

void	init_player(char **map, t_move *player)
{
	int		i;
	int		j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (is_player_init_pos(map[i][j], player))
			{
				player->posx = i;
				player->posy = j;
			}
			j++;
		}
		i++;
	}
}

void	init_game(t_data *data)
{
	ft_memset(&data->player, 0, sizeof(t_move));
	data->player.fov = 60;
	init_player(data->map, &data->player);
	data->player.gravity = 0.05;
	data->player.speed = 0.02;
	data->player.movespeed = data->player.speed;
	data->player.rotspeed = 0.01;
	data->player.wallheight = 5;
	raycasting(data);
}

