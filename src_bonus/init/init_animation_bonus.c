/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_animation_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: endoliam <endoliam@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 14:59:30 by endoliam          #+#    #+#             */
/*   Updated: 2024/10/30 13:13:09 by endoliam         ###   ########lyon.fr   */
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

t_frame	*init_frame(t_data *data, int index, char *prefixe)
{
	t_frame	*anim;
	t_img	img;

	anim = malloc(sizeof(t_frame));
	if (!anim)
		destroy_game(data, EXIT_FAILURE);
	char *i = ft_itoa(index);
	char *cindex = ft_strjoin(prefixe ,i);
	char *path = ft_strjoin(cindex, ".xpm");
	anim->index = index;
	if (!open_image(data, &img, path))
		destroy_game(data, EXIT_FAILURE);
	free(cindex);
	free(path);
	free(i);
	anim->frame = img;
	return (anim);
}

void	init_animation(t_data *data, t_anim *element, char *prefix, int nb)
{
	int			i;
	t_frame		*e_anime;

	i = 0;
	element->animspeed = 0;
	e_anime = element->anim;
	while (i <= nb)
	{
		e_anime = init_frame(data, i, prefix);
		add_stack(&element->anim, e_anime);
		i++;
	}
	while (element->anim && element->anim->prev)
		element->anim = element->anim->prev;
}


