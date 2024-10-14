/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: endoliam <endoliam@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 16:07:51 by sponthus          #+#    #+#             */
/*   Updated: 2024/10/14 14:52:01 by endoliam         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "parsing.h"

// Init valide, manque utilisation

bool	open_image(t_data *data, t_img *img, char *path)
{
	img->img = mlx_xpm_file_to_image(data->mlx, path,
			&img->width, &img->height);
	if (img->img == NULL)
		return (write_err(ERR_OP_TEX, path, NULL, false));
	img->addr = mlx_get_data_addr(img->img, &img->bpp, &img->ll, &img->endian);
	if (!img->addr)
		return (write_err(ERR_OP_TEX, path, NULL, false));
	printf("img %s / img width = %d / height = %d\n", path, img->width, img->height);
	return (true);
}

bool	init_mlx(t_data *data, t_pars *pars)
{
	data->mlx = mlx_init();
	if (!data->mlx)
		return (write_err(ERR_INIT, NULL, "mlx", 1));
	data->win = mlx_new_window(data->mlx, data->win_width,
			data->win_height, "cub3d");
	if (!data->win)
		return (write_err(ERR_INIT, NULL, "window", 1));
	mlx_hook(data->win, 2, 1L << 0, key_press, data);
	mlx_hook(data->win, 3, 1L << 1, key_release, data);
	if (open_image(data, &data->sprites.no, pars->no) == false)
		return (false);
	if (open_image(data, &data->sprites.so, pars->so) == false)
		return (false);
	if (open_image(data, &data->sprites.we, pars->we) == false)
		return (false);
	if (open_image(data, &data->sprites.ea, pars->ea) == false)
		return (false);
	init_game(data);
	return (true);
}
