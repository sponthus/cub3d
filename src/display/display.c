/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sponthus <sponthus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 11:32:39 by endoliam          #+#    #+#             */
/*   Updated: 2024/10/31 14:32:00 by sponthus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "mlx.h"

void	init_img(t_data *data)
{
	data->display.ptr1.img = mlx_new_image(data->mlx, data->win_width,
			data->win_height);
	if (!data->display.ptr1.img)
	{
		write_err("mlx_new_image failed", NULL, NULL, false);
		free_data(data);
		exit(42);
	}
	data->display.ptr1.addr = mlx_get_data_addr(data->display.ptr1.img,
			&data->display.ptr1.bpp, &data->display.ptr1.ll,
			&data->display.ptr1.endian);
}

void	destroy_img(t_data *data)
{
	if (data->display.ptr1.img)
	{
		mlx_put_image_to_window(data->mlx, data->win,
			data->display.ptr1.img, 0, 0);
		mlx_destroy_image(data->mlx, data->display.ptr1.img);
		data->display.ptr1.img = NULL;
	}
}

void	draw_line_pixel(t_data *data, t_raycast *ray, int x, int texx)
{
	unsigned int	color;
	int				y;
	int				pery;

	color = 0;
	y = 0;
	pery = 0;
	while (y <= data->win_height)
	{
		if (y >= ray->drawstart && y <= ray->drawend)
		{
			pery = (y - ray->linestart) * 100 / ray->lineheight;
			color = tex_chose_color(data, pery, texx, ray->dir);
			color = calculate_shaded_color(color, ray->perpwalldist);
			my_mlx_pixel_put(&data->display.ptr1, x, y, color);
		}
		else if (y < ray->drawstart)
			my_mlx_pixel_put(&data->display.ptr1, x, y, data->sprites.ceiling);
		else if (y > ray->drawend)
			my_mlx_pixel_put(&data->display.ptr1, x, y, data->sprites.floor);
		y++;
	}
}

// side = 0 -> mur nord ou sud
void	draw_line(t_data *data, t_raycast *ray, int x, int side)
{
	int		texx;

	ray->dir = chose_dir(side, ray);
	texx = 0;
	if (side == 0)
		texx = calc_texx_y(data, ray);
	else
		texx = calc_texx_x(data, ray);
	draw_line_pixel(data, ray, x, texx);
}

void	update_frame_data(t_data *data)
{
	char		*fps;

	data->player.old_time = data->player.time;
	data->player.time = my_get_time();
	if (data->player.time != data->player.old_time)
		data->player.frame = (data->player.time - data->player.old_time)
			* 0.0001;
	else
		data->player.frame = 0;
	fps = ft_itoa(1 / data->player.frame);
	mlx_string_put(data->mlx, data->win, 0,
		data->win_height - 5, FPS_COLOR, "FPS : ");
	mlx_string_put(data->mlx, data->win, 40,
		data->win_height - 5, FPS_COLOR, fps);
	free(fps);
}
