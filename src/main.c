/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sponthus <sponthus@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 14:39:46 by sponthus          #+#    #+#             */
/*   Updated: 2024/09/17 15:20:21 by sponthus         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "mlx.h"
#include "cub3d.h"

#include <string.h>


int	main(int argc, char **argv)
{
	t_data	data;

	memset(&data, 0, sizeof(t_data));
	init_data(&data);
	if (argc == 2)
	{
		if (parsing(argv[1], &data) == 1)
			return (1);
	}
	else if (argc == 1)
	{
		if (parsing("inc/default.cub", &data) == 1)
			return (1);
	}
	else
		return (1);
	// data.mlx = mlx_init(); // secu
	// data.win = mlx_new_window(data.mlx, data.win_width , data.win_height, "cub3d");
	// init_game(&data);
	// mlx_hook(data.win, 2, 1L<<0, key_press, &data);
	// mlx_hook(data.win, 3, 1L<<1, key_release, &data);
	// mlx_loop_hook(data.mlx, move, &data);
	// mlx_loop(data.mlx);
	return (0);
}
