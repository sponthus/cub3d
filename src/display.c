/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: endoliam <endoliam@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 11:32:39 by endoliam          #+#    #+#             */
/*   Updated: 2024/10/01 00:33:15 by endoliam         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	put_pixel_background(t_data *data, t_img *dis)
{
	int		x = 0;
	int		y = 0;
	unsigned int color1 = 0x00f3aeae; 
	unsigned int color2 = 0x00aef3da;
	unsigned int color = 0;
	double		horizon;
	double		distance;

	horizon = (data->win_height / 2.0) - (data->player.pitch * data->win_height) - data->player.posz;
	while (x < data->win_width)
	{
		y = 0;
		while (y < data->win_height)
		{
			if (y > horizon)
			{
				distance = (y - horizon) / data->win_height;
				color = color1; 
			}
			else
			{
				distance = (horizon - y) / data->win_height;
				color = color2;
			}
			color = calculate_shaded_color(color, (distance * 10));
			my_mlx_pixel_put(dis, x, y, color);
			y++;
		}
		x++;
	}
}

void	init_img(t_data *data)
{
	data->display.ptr1.img = mlx_new_image(data->mlx, data->win_width, data->win_height);
	if (!data->display.ptr1.img)
	{
		printf("error : mlx_new_image failed\n");
		exit(42); // free and exit
	}
	data->display.ptr1.addr = mlx_get_data_addr(data->display.ptr1.img,
	&data->display.ptr1.bpp, &data->display.ptr1.line_length,
							&data->display.ptr1.endian);
}

void	destroy_img(t_data *data)
{
	mlx_put_image_to_window(data->mlx, data->win, data->display.ptr1.img, 0, 0); // protect mlx
	if (data->display.ptr1.img)
		mlx_destroy_image(data->mlx, data->display.ptr1.img);
	data->display.ptr1.img = NULL;
}
