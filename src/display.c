/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: endoliam <endoliam@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 11:32:39 by endoliam          #+#    #+#             */
/*   Updated: 2024/09/13 15:46:40 by endoliam         ###   ########lyon.fr   */
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

void	init_img(t_data *data, int *ptr)
{
	if (data->display.ptr1.img)
	{
		data->display.ptr2.img = mlx_new_image(data->mlx, data->win_width, data->win_height);
		data->display.ptr2.addr = mlx_get_data_addr(data->display.ptr2.img,
		&data->display.ptr2.bpp, &data->display.ptr2.line_length,
								&data->display.ptr2.endian);
		put_pixel_background(data, &data->display.ptr2);
		(*ptr) = 2;
	}
	else
	{
		data->display.ptr1.img = mlx_new_image(data->mlx, data->win_width, data->win_height);
		if (!data->display.ptr1.img)
		{
			printf("error : mlx_new_image failed\n");
			exit(42);
		}
		data->display.ptr1.addr = mlx_get_data_addr(data->display.ptr1.img,
		&data->display.ptr1.bpp, &data->display.ptr1.line_length,
								&data->display.ptr1.endian);
		put_pixel_background(data, &data->display.ptr1);
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
