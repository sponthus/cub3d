/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: endoliam <endoliam@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 14:39:46 by sponthus          #+#    #+#             */
/*   Updated: 2024/11/05 16:20:10 by endoliam         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "mlx.h"
#include "cub3d_bonus.h"

#include <string.h>

void	destoy_frames(t_data *data, t_frame *frame)
{
	t_frame		*to_free;

	if (frame->index != 0)
	{
		while (frame && frame->prev)
			frame = frame->prev;
	}
	while (frame)
	{
		to_free = frame;
		frame = frame->next;
		mlx_destroy_image(data->mlx, to_free->frame.img);
		free(to_free);
	}
}

void	free_animation(t_data *data)
{
	destoy_frames(data, data->menu.background.anim);
	destoy_frames(data, data->menu.icone.anim);
	destoy_frames(data, data->menu.resume.anim);
	destoy_frames(data, data->menu.setting.anim);
	destoy_frames(data, data->menu.exit.anim);
	destoy_frames(data, data->menu.setting_menu.cam.anim);
	destoy_frames(data, data->menu.setting_menu.speed.anim);
	destoy_frames(data, data->menu.setting_menu.color.anim);
	destoy_frames(data, data->menu.setting_menu.barre.anim);
	//destoy_frames(data, data->menu.setting_menu.cursor.anim);
}

int	destroy_game(t_data *data, int exit_status)
{
	if (data->display.ptr1.img)
		mlx_destroy_image(data->mlx, data->display.ptr1.img);
	data->display.ptr1.img = NULL;
	free_animation(data);
	free_data(data);
	exit(exit_status);
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
	if (data->sprites.we.img)
		mlx_destroy_image(data->mlx, data->sprites.door.img);
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
