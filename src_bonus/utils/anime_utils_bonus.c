/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   anime_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: endoliam <endoliam@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 11:52:39 by endoliam          #+#    #+#             */
/*   Updated: 2024/11/08 12:13:27 by endoliam         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"
#include "game_bonus.h"

void	add_stack(t_frame **anim, t_frame *element)
{
	if (!*anim)
	{
		*anim = element;
		element->prev = NULL;
		(*anim)->next = NULL;
	}
	else
	{
		while ((*anim)->next)
			*anim = (*anim)->next;
		(*anim)->next = element;
		element->prev = *anim;
		(*anim) = (*anim)->next;
		(*anim)->next = NULL;
	}
}

void	free_path_anime(char *i, char *cindex, char*path)
{
	free(cindex);
	free(path);
	free(i);
}