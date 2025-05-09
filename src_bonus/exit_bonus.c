/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sponthus <sponthus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 14:56:13 by endoliam          #+#    #+#             */
/*   Updated: 2024/11/12 10:42:22 by sponthus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"
#include "utils.h"
#include "mlx.h"

void	destoy_frames(t_data *data, t_frame *frame)
{
	t_frame		*to_free;

	if (frame && frame->index != 0)
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
