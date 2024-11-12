/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   anime_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sponthus <sponthus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 11:52:39 by endoliam          #+#    #+#             */
/*   Updated: 2024/11/12 10:54:45 by sponthus         ###   ########.fr       */
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

// void	free_path_anime(char *i, char *cindex, char*path)
// {
// 	if (cindex)
// 		free(cindex);
// 	if (path)
// 		free(path);
// 	if (i)
// 		free(i);
// }

bool	is_anime_element(t_data *data, int flag)
{
	if (data->statement == SETTING_MENU)
	{
		if ((data->menu.setting_menu.setting_state == MOVESPEED
				&& flag == SPEED_ANIMATION)
			|| (data->menu.setting_menu.setting_state == ROTSPEED
				&& flag == CAM_ANIMATION)
			|| (data->menu.setting_menu.setting_state == COLOR_SKY
				&& flag == COLOR_ANIMATION)
			|| (data->menu.setting_menu.setting_state == COLOR_FLOOR
				&& flag == COLOR_ANIMATION))
			return (true);
	}
	else if ((data->menu.state_menu == RESUME && flag == RESUME_ANIMATION)
		|| (data->menu.state_menu == SETTING && flag == SETTING_ANIMATION)
		|| (data->menu.state_menu == EXIT && flag == EXIT_ANIMATION))
		return (true);
	return (false);
}

bool	is_icone_color(t_data *data, int flag, int content)
{
	if (content == SKY)
	{
		if ((data->menu.setting_menu.color_state == RED
				&& flag == RED_SKY_ANIMATION)
			|| (data->menu.setting_menu.color_state == GREEN
				&& flag == GREEN_SKY_ANIMATION)
			|| (data->menu.setting_menu.color_state == BLUE
				&& flag == BLUE_SKY_ANIMATION))
			return (true);
	}
	else if (content == FLOOR)
	{
		if ((data->menu.setting_menu.color_state == RED
				&& flag == RED_FLOOR_ANIMATION)
			|| (data->menu.setting_menu.color_state == GREEN
				&& flag == GREEN_FLOOR_ANIMATION)
			|| (data->menu.setting_menu.color_state == BLUE
				&& flag == BLUE_FLOOR_ANIMATION))
			return (true);
	}
	return (false);
}

bool	is_setting_icone(t_data *data, int flag)
{
	if (data->statement == SETTING_MENU)
	{
		if ((data->menu.setting_menu.setting_state == COLOR_SKY
				&& is_icone_color(data, flag, SKY))
			|| (data->menu.setting_menu.setting_state == COLOR_FLOOR
				&& is_icone_color(data, flag, FLOOR))
			|| (data->menu.setting_menu.setting_state == MOVESPEED
				&& flag == CURS_SPEED_ANIMATION)
			|| (data->menu.setting_menu.setting_state == ROTSPEED
				&& flag == CURS_CAM_ANIMATION))
			return (true);
	}
	return (false);
}
