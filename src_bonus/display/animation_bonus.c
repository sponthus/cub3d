/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sponthus <sponthus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 22:28:16 by endoliam          #+#    #+#             */
/*   Updated: 2024/11/12 10:07:54 by sponthus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"
#include "game_bonus.h"
#include "mlx.h"

void	got_next_frame(t_anim *element)
{
	if (element->animspeed > 1 && element->anim->next)
	{
		element->animspeed = 0;
		element->anim = element->anim->next;
	}
}

void	update_frame(t_data *data, t_anim *element, int v)
{
	element->animspeed += data->player.frame * v;
	if (!element->anim->next)
	{
		while (element->anim && element->anim->prev)
			element->anim = element->anim->prev;
	}
	got_next_frame(element);
}

void	update_frame_data(t_data *data)
{
	char		*fps;

	data->player.old_time = data->player.time;
	data->player.time = my_get_time();
	if (data->player.time != data->player.old_time)
		data->player.frame = (data->player.time - data->player.old_time)
			* 0.0002;
	else
		data->player.frame = 0;
	fps = ft_itoa(1 / data->player.frame);
	mlx_string_put(data->mlx, data->win, 0,
		data->win_height - 5, 0x0fdf9411, "FPS : ");
	mlx_string_put(data->mlx, data->win, 40,
		data->win_height - 5, 0x0fdf9411, fps);
	free(fps);
}
