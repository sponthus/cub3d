/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: endoliam <endoliam@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 22:28:16 by endoliam          #+#    #+#             */
/*   Updated: 2024/10/17 15:05:16 by endoliam         ###   ########lyon.fr   */
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
