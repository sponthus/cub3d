/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: endoliam <endoliam@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 14:39:46 by sponthus          #+#    #+#             */
/*   Updated: 2024/09/11 16:04:27 by endoliam         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "mlx.h"
#include "cub3d.h"
#include <X11/keysym.h>
#include <string.h>

int	key_release(int keycode, t_data *data)
{
	if (keycode == XK_Escape)
		data->key.esc = 0;
	if (keycode == XK_z)
		data->key.z = 0;
	if (keycode == XK_s)
		data->key.s = 0;
	if (keycode == XK_q)
		data->key.q = 0;
	if (keycode == XK_d)
		data->key.d = 0;
	if (keycode == XK_c)
		data->key.c = 0;
	if (keycode == XK_Left)
		data->key.left = 0;
	if (keycode == XK_Right)
		data->key.right = 0;
	if (keycode == XK_Up)
		data->key.up = 0;
	if (keycode == XK_Down)
		data->key.down = 0;
	if (keycode == XK_Shift_L)
		data->key.tab = 0;
	return (0);
}

int	press(int keycode, t_data *data)
{
	//printf("%d ", keycode);
	if (keycode == XK_Escape)
	{
		if (data->display.ptr2.img)
			mlx_destroy_image(data->mlx, data->display.ptr2.img);
		if (data->display.ptr1.img)
			mlx_destroy_image(data->mlx, data->display.ptr1.img);
		mlx_destroy_window(data->mlx, data->win);
		mlx_destroy_display(data->mlx);
		exit (0);
	}
	//if (keycode == XK_Escape)
	//	data->key.esc = 1;
	if (keycode == XK_z)
		data->key.z = 1;
	if (keycode == XK_s)
		data->key.s = 1;
	if (keycode == XK_q)
		data->key.q = 1;
	if (keycode == XK_d)
		data->key.d = 1;
	if (keycode == XK_c)
		data->key.c = 1;
	if (keycode == XK_Left)
		data->key.left = 1;
	if (keycode == XK_Right)
		data->key.right = 1;
	if (keycode == XK_Up)
		data->key.up = 1;
	if (keycode == XK_Down)
		data->key.down = 1;
	if (keycode == XK_Shift_L)
		data->key.tab = 1;
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	data;

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
	memset(&data, 0, sizeof(t_data));
	data.mlx = mlx_init(); // secu
	data.win = mlx_new_window(data.mlx, 800, 800, "cub3d");
	init_game(&data);
	mlx_hook(data.win, 2, 1L<<0, press, &data);
	mlx_hook(data.win, 3, 1L<<1, key_release, &data);
	mlx_loop_hook(data.mlx, move, &data);
	mlx_loop(data.mlx);
	(void)argc;
	(void)argv;
	return (0);
}
