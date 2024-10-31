/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sponthus <sponthus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 10:51:49 by sponthus          #+#    #+#             */
/*   Updated: 2024/10/31 15:49:27 by sponthus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

unsigned int	chose_minimap_color(t_data *data, int x, int y)
{
	double	beg_x;
	double	beg_y;
	int		map_x;
	int		map_y;

	beg_x = data->player.posx - ((double)MINIMAP_WIDTH * 0.5) / TILE_SIZE;
	beg_y = data->player.posy + ((double)MINIMAP_HEIGHT * 0.5) / TILE_SIZE;
	map_x = (int)(beg_x + (double)y / (double)TILE_SIZE);
	map_y = (int)(beg_y - (double)x / (double)TILE_SIZE);
	if (map_x >= 0 && map_x < map_size(data) && map_y >= 0
		&& map_y < map_length(data))
	{
		if (data->map[map_x][map_y] == '0')
			return (COL_EMPTY);
		else if (data->map[map_x][map_y] == 'O')
			return (COL_OPEN);
		else if (data->map[map_x][map_y] == 'D')
			return (COL_DOOR);
	}
	return (COL_BACK);
}

void	draw_player(t_data *data, int basex, int basey)
{
	int	x;
	int	y;

	x = 0;
	while (x < 5)
	{
		y = 0;
		while (y < 5)
		{
			my_mlx_pixel_put(&data->display.ptr1, basex - 2
				+ MINIMAP_HEIGHT * 0.5 + x, basey - 2 + MINIMAP_WIDTH * 0.5
				+ y, COL_PLAYER);
			y++;
		}
		x++;
	}
}

void	draw_contours(t_data *data, int basex, int basey)
{
	int	x;

	x = 0;
	while (x <= MINIMAP_WIDTH)
	{
		my_mlx_pixel_put(&data->display.ptr1, basex, basey + x, COL_CONT);
		my_mlx_pixel_put(&data->display.ptr1, basex + MINIMAP_HEIGHT, \
			basey + x, COL_CONT);
		x++;
	}
	x = 0;
	while (x <= MINIMAP_HEIGHT)
	{
		my_mlx_pixel_put(&data->display.ptr1, basex + x, basey, COL_CONT);
		my_mlx_pixel_put(&data->display.ptr1, basex + x, basey \
			+ MINIMAP_WIDTH, COL_CONT);
		x++;
	}
}

void	draw_minimap(t_data *data)
{
	int				x;
	int				y;
	int				basex;
	int				basey;
	unsigned int	color;

	if (MINIMAP_HEIGHT >= WIN_HEIGHT - 100 || MINIMAP_WIDTH >= WIN_WIDTH - 100)
		return ;
	x = 0;
	basex = 15;
	basey = 15;
	while (x <= MINIMAP_HEIGHT)
	{
		y = 0;
		while (y <= MINIMAP_WIDTH)
		{
			color = chose_minimap_color(data, x, y);
			my_mlx_pixel_put(&data->display.ptr1, basex + x, basey + y, color);
			y++;
		}
		x++;
	}
	draw_player(data, basex, basey);
	draw_contours(data, basex, basey);
}
