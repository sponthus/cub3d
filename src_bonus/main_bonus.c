/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sponthus <sponthus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 14:39:46 by sponthus          #+#    #+#             */
/*   Updated: 2024/11/12 10:12:40 by sponthus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "cub3d_bonus.h"
#include "parsing_bonus.h"
#include "errors_bonus.h"

int	display_game(t_data *data)
{
	if (data->statement == PLAY)
	{
		data->menu.background.y = data->win_height;
		data->menu.state_menu = RESUME;	
		move(data);
	}
	else if (data->statement == PAUSE)
		pause_game(data);
	else if (data->statement == SETTING_MENU)
		setting_menu(data);
	// else if (data->statement == MENU)
	// 	main_menu(data);
	return (0);
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
		if (parsing("inc_bonus/default.cub", &data) == 1)
		{
			free_data(&data);
			return (1);
		}
	}
	else
		return (write_err(ERR_COUNT, EXP_CUB, "arguments", 1));
	mlx_loop_hook(data.mlx, display_game, &data);
	mlx_loop(data.mlx);
	return (0);
}
