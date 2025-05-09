/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sponthus <sponthus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 14:39:46 by sponthus          #+#    #+#             */
/*   Updated: 2024/10/31 14:25:32 by sponthus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "cub3d.h"
#include "utils.h"
#include "errors.h"

int	destroy_game(t_data *data, int exit_code)
{
	if (data->display.ptr1.img)
		mlx_destroy_image(data->mlx, data->display.ptr1.img);
	data->display.ptr1.img = NULL;
	free_data(data);
	exit(exit_code);
}

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
	else
		return (write_err(ERR_COUNT, EXP_CUB, "arguments", 1));
	mlx_loop_hook(data.mlx, move, &data);
	mlx_loop(data.mlx);
	return (0);
}
