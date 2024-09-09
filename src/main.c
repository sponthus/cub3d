/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sponthus <sponthus@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 14:39:46 by sponthus          #+#    #+#             */
/*   Updated: 2024/09/09 16:49:55 by sponthus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "mlx.h"
#include "cub3d.h"
#include <X11/keysym.h>

int	press(int keycode, t_data *data)
{
	printf("%d ", keycode);
	if (keycode == XK_Escape)
		mlx_destroy_window(data->mlx, data->win);
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	data;

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

	data.mlx = mlx_init(); // secu
	data.win = mlx_new_window(data.mlx, 600, 600, "cub3d");
	mlx_hook(data.win, 2, 1L<<0, press, &data);
	mlx_loop(data.mlx);
}
