/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sponthus <sponthus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 16:07:51 by sponthus          #+#    #+#             */
/*   Updated: 2024/09/23 14:27:00 by sponthus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "parsing.h"

bool	open_image(void *mlx, t_img *img, char *path, int *size)
{
	img->img = mlx_xpm_file_to_image(mlx, path, size, size);
	if (img->img == NULL)
	{
		return (write_err(ERR_OP_TEX, path, NULL, false));
	}
	return (true);
}

bool	init_mlx(t_data *data, t_pars *pars)
{
	data->mlx = mlx_init();
	if (!data->mlx)
		return (write_err(ERR_INIT, NULL, "mlx", 1));
	data->win = mlx_new_window(data->mlx, data->win_width, data->win_height, "cub3d");
	if (!data->win)
		return (write_err(ERR_INIT, NULL, "window", 1));
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
