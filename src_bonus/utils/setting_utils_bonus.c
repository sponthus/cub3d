/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setting_utils_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: endoliam <endoliam@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 13:59:48 by endoliam          #+#    #+#             */
/*   Updated: 2024/11/08 14:45:57 by endoliam         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int	calcul_cursorx(t_data *data, int cursor)
{
	return (cursor * data->menu.setting_menu.barre.scale_x
		+ data->menu.setting_menu.barre.x
		- ((data->menu.setting_menu.cursor->anim->frame.height) * 0.5
			* data->menu.setting_menu.cursor->scale_x));
}

int	set_flag_color(t_data *data, t_color_cursor cursor, int flag)
{
	if (cursor.r == data->menu.setting_menu.cursor_floor.r
		&& cursor.g == data->menu.setting_menu.cursor_floor.g
		&& cursor.b == data->menu.setting_menu.cursor_floor.b)
		flag++;
	return (flag);
}

void	put_line(t_data *data, int basex, int basey, int cursor)
{
	data->menu.setting_menu.barre.x = basex;
	data->menu.setting_menu.barre.y = basey;
	put_button(data, &data->menu.setting_menu.barre, BAR_ANIMATION);
	data->menu.setting_menu.cursor->x = calcul_cursorx(data, cursor);
	data->menu.setting_menu.cursor->y = basey
		+ (30 * data->menu.setting_menu.barre.scale_y);
}

void	put_cursor(t_data *data, int flag, t_color_cursor *c_cursor)
{
	if (c_cursor)
		flag = set_flag_color(data, *(c_cursor), flag);
	put_button(data, data->menu.setting_menu.cursor, flag);
}
