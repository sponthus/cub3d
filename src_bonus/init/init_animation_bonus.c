/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_animation_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: endoliam <endoliam@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 14:59:30 by endoliam          #+#    #+#             */
/*   Updated: 2024/11/08 13:07:48 by endoliam         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"
#include "game_bonus.h"

t_frame	*init_frame(t_data *data, int index, char *prefixe)
{
	t_frame	*anim;
	t_img	img;
	char	*i;
	char	*cindex;
	char	*path;

	anim = malloc(sizeof(t_frame));
	if (!anim)
		destroy_game(data, EXIT_FAILURE);
	i = ft_itoa(index);
	cindex = ft_strjoin(prefixe, i);
	path = ft_strjoin(cindex, ".xpm");
	anim->index = index;
	if (!path || !open_image(data, &img, path))
	{
		free(anim);
		free_path_anime(i, cindex, path);
		destroy_game(data, EXIT_FAILURE);
	}
	free_path_anime(i, cindex, path);
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
