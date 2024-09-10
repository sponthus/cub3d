/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: endoliam <endoliam@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 14:39:46 by sponthus          #+#    #+#             */
/*   Updated: 2024/09/10 12:38:04 by endoliam         ###   ########lyon.fr   */
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
	{
		mlx_destroy_window(data->mlx, data->win);
		exit (0);
	}
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
	(void)argc;
	(void)argv;
	data.mlx = mlx_init(); // secu
	data.win = mlx_new_window(data.mlx, 800, 800, "cub3d");
	mlx_hook(data.win, 2, 1L<<0, press, &data);
	mlx_loop(data.mlx);
	return (0);
}
