/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: endoliam <endoliam@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 22:28:16 by endoliam          #+#    #+#             */
/*   Updated: 2024/10/29 16:25:55 by endoliam         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"
#include "game_bonus.h"

void	update_frame(t_data *data, t_anim *element, int v)
{
	element->animspeed += data->player.frame * v;
	if (!element->anim->next)
	{	
		while (element->anim && element->anim->prev)
			element->anim = element->anim->prev;
	}
	if (element->animspeed > 1 && element->anim->next)
	{
		element->animspeed = 0;			
		element->anim = element->anim->next;
	}
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
