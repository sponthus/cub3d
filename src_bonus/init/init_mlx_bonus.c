/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sponthus <sponthus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 16:07:51 by sponthus          #+#    #+#             */
/*   Updated: 2024/11/13 12:17:33 by sponthus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"
#include "parsing_bonus.h"
#include "errors_bonus.h"
#include "mlx.h"

bool	open_image(t_data *data, t_img *img, char *path)
{
	img->img = mlx_xpm_file_to_image(data->mlx, path,
			&img->width, &img->height);
	if (img->img == NULL)
		return (write_err(ERR_OP_TEX, path, NULL, false));
	img->addr = mlx_get_data_addr(img->img, &img->bpp, &img->ll, &img->endian);
	if (!img->addr)
		return (write_err(ERR_OP_TEX, path, NULL, false));
	return (true);
}

void	init_data(t_data *data)
{
	if (WIN_HEIGHT < 100 || WIN_WIDTH < 100)
	{
		write_err(ERR_WIN_SIZE, NULL, NULL, 42);
		exit(EXIT_FAILURE);
	}
	data->win_height = WIN_HEIGHT;
	data->win_width = WIN_WIDTH;
	data->map = NULL;
	data->mlx = NULL;
	data->win = NULL;
}

void	init_parsing(t_pars *pars)
{
	pars->no = NULL;
	pars->so = NULL;
	pars->we = NULL;
	pars->ea = NULL;
	pars->floor_color = NULL;
	pars->ceiling_color = NULL;
	pars->fd = -1;
	pars->file = NULL;
	pars->lst_file = NULL;
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
	mlx_hook(data->win, 17, 0, destroy_game, data);
	if (open_image(data, &data->sprites.no, pars->no) == false)
		return (false);
	if (open_image(data, &data->sprites.so, pars->so) == false)
		return (false);
	if (open_image(data, &data->sprites.we, pars->we) == false)
		return (false);
	if (open_image(data, &data->sprites.ea, pars->ea) == false)
		return (false);
	if (open_image(data, &data->sprites.door, DOOR_TEXTURE) == false)
		return (false);
	return (true);
}
