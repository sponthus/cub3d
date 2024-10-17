/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sponthus <sponthus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 10:51:49 by sponthus          #+#    #+#             */
/*   Updated: 2024/10/17 15:40:31 by sponthus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int	chose_minimap_color(t_data *data, int x, int y)
{
	int	relposx;
	int	relposy;

	relposx = ((x * map_size(data) * 6) / (data->win_height)) - data->player.posx / 2;
	relposy = ((y * map_length(data) * 6) / data->win_width ) - data->player.posy / 2;
	// printf("x = %d - y = %d - realposx = %d - realposy = %d\n", x, y, relposx, relposy);
	if (relposy <= 0 || relposy >= map_length(data) - 1)
		return (0x000000);
	else if (relposx <= 0 || relposx >= map_size(data) - 1)
		return (0x000000);
	else if (data->map[relposx][relposy] == '1')
		return (0x000000);
	else if (data->map[relposx][relposy] == '0')
		return (0xFFFFFF);
	return (0x000000);
}

void	draw_player(t_data *data)
{
	int x;
	int	y;

	x = 0;
	while (x < 5)
	{
		y = 0;
		while (y < 5)
		{
			my_mlx_pixel_put(&data->display.ptr1, basex + (data->win_height / 12) + x, basey + (data->win_width / 12) + y, 0xFFE0);
			y++;
		}
		x++;
	}
}

void	draw_minimap(t_data *data)
{
	int	x;
	int	y;
	int	basex;
	int	basey;
	unsigned int	color;

	x = 0;
	basex = (data->win_height / 16) * 13;
	basey = (data->win_width / 16) * 13;
	while (x < data->win_height / 6)
	{
		y = 0;
		while (y < data->win_width / 6)
		{
			color = chose_minimap_color(data, x, y);
			my_mlx_pixel_put(&data->display.ptr1, basex + x, basey + y, color);
			y++;
		}
		x++;
	}
	draw_player(data);
}
