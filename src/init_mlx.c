/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sponthus <sponthus@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 16:07:51 by sponthus          #+#    #+#             */
/*   Updated: 2024/09/17 17:00:04 by sponthus         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "parsing.h"

bool	open_image(void *mlx, t_img *img, char *path, int *size)
{
	img->img = mlx_xpm_file_to_image(mlx, path, size, size);
	if (img->img == NULL)
	{
		return (write_error("Could not open texture", path, false));
	}
	return (true);
}

bool	init_mlx(t_data *data, t_pars *pars)
{
	data->mlx = mlx_init(); // secu
	if (!data->mlx)
		return (write_error("Failed to init mlx", NULL, 1));
	data->win = mlx_new_window(data->mlx, data->win_width , data->win_height, "cub3d");
	if (!data->win)
		return (write_error("Failed to init window", NULL, 1));
	init_game(data);
	mlx_hook(data->win, 2, 1L<<0, key_press, data);
	mlx_hook(data->win, 3, 1L<<1, key_release, data);
	if (open_image(data->mlx, &data->sprites.no, pars->no, &data->sprites.size) == false)
		return (false);
	if (open_image(data->mlx, &data->sprites.so, pars->so, &data->sprites.size) == false)
		return (false);
	if (open_image(data->mlx, &data->sprites.we, pars->we, &data->sprites.size) == false)
		return (false);
	if (open_image(data->mlx, &data->sprites.ea, pars->ea, &data->sprites.size) == false)
		return (false);
	return (true);
}

	// data->sprites.so.img = mlx_xpm_file_to_image(data->mlx, pars->so, &data->sprites.size, &data->sprites.size);
	// if (data->sprites.so.img == NULL)
	// 	return (write_error("Could not open texture", pars->so, false));
	// data->sprites.ea.img = mlx_xpm_file_to_image(data->mlx, pars->ea, &data->sprites.size, &data->sprites.size);
	// if (data->sprites.ea.img == NULL)
	// 	return (write_error("Could not open texture", pars->ea, false));
	// data->sprites.we.img = mlx_xpm_file_to_image(data->mlx, pars->we, &data->sprites.size, &data->sprites.size);
	// if (data->sprites.we.img == NULL)
	// 	return (write_error("Could not open texture", pars->we, false));