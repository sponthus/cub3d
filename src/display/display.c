/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: endoliam <endoliam@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 11:32:39 by endoliam          #+#    #+#             */
/*   Updated: 2024/10/14 16:35:35 by endoliam         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	pause_game(t_data *data)
{
	if (data->display.ptr1.img)
		mlx_destroy_image(data->mlx, data->display.ptr1.img);
	data->display.ptr1.img = NULL;
	mlx_string_put(data->mlx, data->win, data->win_width * 0.5,
		data->win_height * 0.5 , 0x0fdf9411, "PAUSE");
}

int	display_game(t_data *data)
{	
	if (data->statement == PLAY)
		move(data);
	else if (data->statement == PAUSE)
		pause_game(data);
	return (0);
}

void	init_img(t_data *data)
{
	data->display.ptr1.img = mlx_new_image(data->mlx, data->win_width,
			data->win_height);
	if (!data->display.ptr1.img)
	{
		printf("error : mlx_new_image failed\n");
		exit(42); // free and exit
	}
	data->display.ptr1.addr = mlx_get_data_addr(data->display.ptr1.img,
			&data->display.ptr1.bpp, &data->display.ptr1.ll,
			&data->display.ptr1.endian);
}

void	destroy_img(t_data *data)
{
	mlx_put_image_to_window(data->mlx, data->win,
		data->display.ptr1.img, 0, 0); // protect mlx
	if (data->display.ptr1.img)
		mlx_destroy_image(data->mlx, data->display.ptr1.img);
	data->display.ptr1.img = NULL;
}

// Nom pas fou mais je pense que le + approprie derait draw_line
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

/*  FONCTIONNE MAIS A SYNTHETISER */
void	draw_line(t_data *data, t_raycast *ray, int x, int side)
{
	int		texx;

	ray->dir = chose_dir(side, ray);
	texx = 0;
	if (side == 0) // Mur nord ou sud
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
		data->win_height - 5, 0x0fdf9411, "FPS : ");
	mlx_string_put(data->mlx, data->win, 40,
		data->win_height - 5, 0x0fdf9411, fps);
	free(fps);
}
