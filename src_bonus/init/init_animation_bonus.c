/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_animation_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: endoliam <endoliam@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 14:59:30 by endoliam          #+#    #+#             */
/*   Updated: 2024/11/13 10:24:13 by endoliam         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"
#include "game_bonus.h"
#include "utils_bonus.h"

char	*anime_path(int index, char *prefixe)
{
	char	*path;
	char	*i;
	char	*cindex;

	path = NULL;
	i = ft_itoa(index);
	cindex = ft_strjoin(prefixe, i);
	path = ft_strjoin(cindex, ".xpm");
	free(i);
	free(cindex);
	return (path);
}

// Function modified to suppress compilation warning,
// added anime_path to create name
t_frame	*init_frame(t_data *data, int index, char *prefixe)
{
	t_frame	*anim;
	t_img	img;
	char	*path;

	anim = malloc(sizeof(t_frame));
	if (!anim)
		destroy_game(data, EXIT_FAILURE);
	anim->index = index;
	path = anime_path(index, prefixe);
	if (!path)
	{
		free(anim);
		destroy_game(data, EXIT_FAILURE);
	}
	if (!open_image(data, &img, path))
	{
		free(path);
		free(anim);
		destroy_game(data, EXIT_FAILURE);
	}
	free(path);
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
