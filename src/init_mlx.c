/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sponthus <sponthus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 16:07:51 by sponthus          #+#    #+#             */
/*   Updated: 2024/10/03 11:20:30 by sponthus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "parsing.h"

// CA MARCHE PAS ENCORE DU TOUT

// t_img	*init_image(t_data *data, t_img *img, char *path, int *size)
// {
// 	ft_memset(&img, 0, sizeof(img));
// 	img->img = mlx_xpm_file_to_image(data->mlx, path, size, size);
// 	if (img->img == NULL)
// 	{
// 		write_err(ERR_OP_TEX, path, NULL, 0);
// 		return (NULL);
// 	}
// 	img->addr = (char *)mlx_get_data_addr(img->img, &img->bpp, &img->ll, &img->endian);
// 	return (img);
// }

bool	open_image(t_data *data, char *txt, char *path, int *size)
{
	t_img	*tmp;
	int		x;
	int		y;

	x = 0;
	// tmp = init_image(data, tmp, path, size);
	// if (!tmp)
	// 	return (false);
	// txt = ft_calloc(1, sizeof * txt * *size * *size);
	// if (!txt)
	// 	return (write_err(ERR_MALLOC, NULL, NULL, false));
	// while (x < *size)
	// {
	// 	y = 0;
	// 	while (y < *size)
	// 	{
	// 		txt[x * *size + y] = tmp->addr[x * *size + y];
	// 		++y;
	// 	}
	// 	x++;
	// }
	// mlx_destroy_image(data->mlx, tmp->img);
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
	// if (open_image(data, data->sprites.no, pars->no, &pars->size) == false)
	// 	return (false);
	// if (open_image(data, data->sprites.so, pars->so, &pars->size) == false)
	// 	return (false);
	// if (open_image(data, data->sprites.we, pars->we, &pars->size) == false)
	// 	return (false);
	// if (open_image(data, data->sprites.ea, pars->ea, &pars->size) == false)
	// 	return (false);
	return (true);
}
