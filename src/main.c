/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sponthus <sponthus@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 14:39:46 by sponthus          #+#    #+#             */
/*   Updated: 2024/09/09 16:36:15 by sponthus         ###   ########.fr       */
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

int	main(void)
{
	t_data	data;

	data.mlx = mlx_init(); // secu
	data.win = mlx_new_window(data.mlx, 600, 600, "cub3d");
	mlx_hook(data.win, 2, 1L<<0, press, &data);
	mlx_loop(data.mlx);
}
