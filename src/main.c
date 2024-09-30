/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: endoliam <endoliam@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 14:39:46 by sponthus          #+#    #+#             */
/*   Updated: 2024/09/30 20:16:34 by endoliam         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "mlx.h"
#include "cub3d.h"

#include <string.h>

void	free_data(t_data *data)
{
	if (data->map)
		free_full_split(data->map);
	if (data->sprites.no.img)
		mlx_destroy_image(data->mlx, data->sprites.no.img);
	if (data->sprites.so.img)
		mlx_destroy_image(data->mlx, data->sprites.so.img);
	if (data->sprites.ea.img)
		mlx_destroy_image(data->mlx, data->sprites.ea.img);
	if (data->sprites.we.img)
		mlx_destroy_image(data->mlx, data->sprites.we.img);
	if (data->win)
		mlx_destroy_window(data->mlx, data->win);
	if (data->mlx)
	{
		mlx_destroy_display(data->mlx);
		free(data->mlx);
	}
}

int	main(int argc, char **argv)
{
	t_data	data;

	ft_memset(&data, 0, sizeof(t_data));
	init_data(&data);
	if (argc == 2)
	{
		if (parsing(argv[1], &data) == 1)
		{
			free_data(&data);
			return (1);
		}
	}
	else if (argc == 1) // Ca va partir en version finale
	{
		if (parsing("inc/default.cub", &data) == 1)
		{
			free_data(&data);
			return (1);
		}
	}
	else
		return (write_err(ERR_COUNT, EXP_CUB, "arguments", 1));
	// coucou Sarah tu j'ai initialiser le jeux en fonction de la pos et la direction du player
	// j'ai aussi fais des couleurs en fonctions de la direction du mur pour me reperer
	// tu verras aussi j'ai eloigner la distance qui separe le player du mur pour que ça soit plus visible
	// actuellement je met en place les sprite que tu as init
	// des bisous <3
	mlx_hook(data.win, 2, 1L<<0, key_press, &data);
	mlx_hook(data.win, 3, 1L<<1, key_release, &data);
	mlx_loop_hook(data.mlx, move, &data);
	mlx_loop(data.mlx);
	return (0);
}
