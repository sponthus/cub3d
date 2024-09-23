/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sponthus <sponthus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 14:39:46 by sponthus          #+#    #+#             */
/*   Updated: 2024/09/23 12:11:33 by sponthus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "mlx.h"
#include "cub3d.h"

#include <string.h>

void	free_data(t_data *data)
{
	if (data->map != NULL)
		free_full_split(data->map);
}

int	main(int argc, char **argv)
{
	t_data	data;

	memset(&data, 0, sizeof(t_data));
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
		return (write_error("Wrong number of arguments", "expected only file.cub", NULL, 1));
	
	// Coucou c'est Sarah, j'ai init la MLX dans le parsing, tu trouveras l'init dans init_mlx
	// Bisous 1
	
	// data.mlx = mlx_init(); // secu
	// if (!data.mlx)
	// 	return (write_error("Failed to init mlx", NULL, 1));
	// data.win = mlx_new_window(data.mlx, data.win_width , data.win_height, "cub3d");
	// if (!data.win)
	// 	return (write_error("Failed to init window", NULL, 1));
	// init_game(&data);
	// mlx_hook(data.win, 2, 1L<<0, key_press, &data);
	// mlx_hook(data.win, 3, 1L<<1, key_release, &data);

	// Ca je l'ai laisse la jsp ca me disait bien
	mlx_loop_hook(data.mlx, move, &data);
	mlx_loop(data.mlx);
	return (0);
}
