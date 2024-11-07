/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keypress_menu_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: endoliam <endoliam@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 14:07:14 by endoliam          #+#    #+#             */
/*   Updated: 2024/11/07 15:52:59 by endoliam         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h" 

void	set_move_data(double *max, double *min, double *spe, t_data *data)
{
	if (data->menu.setting_menu.setting_state == MOVESPEED)
	{
		*(min) = MIN_SPEED;
		*(max) = MAX_SPEED;
		*(spe) = 0.001;
	}
	else if (data->menu.setting_menu.setting_state == ROTSPEED)
	{
		*(min) = MIN_ROT;
		*(max) = MAX_ROT;
		*(spe) = 0.0001;
	}
}

void	move_speed_cursor(int keycode, int *cursor, double *speed, t_data *data)
{
	double	min;
	double	max;
	double	spe;

	set_move_data(&max, &min, &spe, data);
	if (keycode == XK_Right && *(speed) <= max)
	{
		*(cursor) += 10;
		*(speed) += spe;
	}
	else if (keycode == XK_Left && *(speed) > min)
	{
		*(cursor) -= 10;
		*(speed) -= spe;
	}
}

void	set_enum_setting(int keycode, t_data *data)
{
	if (keycode == XK_Up)
	{
		if (data->menu.setting_menu.setting_state >= COLOR_SKY
			&& data->menu.setting_menu.color_state != RED)
			data->menu.setting_menu.color_state--;
		else if (data->menu.setting_menu.setting_state != MOVESPEED)
		{
			data->menu.setting_menu.color_state = BLUE;
			data->menu.setting_menu.setting_state--;
		}
	}
	else if (keycode == XK_Down)
	{
		if (data->menu.setting_menu.setting_state >= COLOR_SKY
			&& data->menu.setting_menu.color_state != BLUE)
			data->menu.setting_menu.color_state++;
		else if (data->menu.setting_menu.setting_state != COLOR_FLOOR)
		{
			data->menu.setting_menu.color_state = RED;
			data->menu.setting_menu.setting_state++;
		}
	}
}

void	key_press_for_setting_menu(int keycode, t_data *data)
{
	if (keycode == XK_BackSpace)
	{
		data->menu.setting_menu.setting_state = MOVESPEED;
		data->statement = PAUSE;
	}
	else if (keycode == XK_Down || keycode == XK_Up)
		set_enum_setting(keycode, data);
	else if (data->menu.setting_menu.setting_state == MOVESPEED)
		move_speed_cursor(keycode,
			&data->menu.setting_menu.cursor_speed,
			&data->player.movespeed, data);
	else if (data->menu.setting_menu.setting_state == ROTSPEED)
		move_speed_cursor(keycode,
			&data->menu.setting_menu.cursor_cam,
			&data->player.rotspeed, data);
	else if (data->menu.setting_menu.setting_state == COLOR_SKY
		|| data->menu.setting_menu.setting_state == COLOR_FLOOR)
		keypress_move_color(keycode, data);
}

void	key_press_for_menu(int keycode, t_data *data)
{
	if (keycode == XK_KP_Enter || keycode == XK_Return)
	{
		if (data->menu.state_menu == RESUME)
			data->statement = PLAY;
		else if (data->menu.state_menu == EXIT)
			destroy_game(data, EXIT_SUCCESS);
		else if (data->menu.state_menu == SETTING)
			data->statement = SETTING_MENU;
	}
	else if (keycode == XK_BackSpace)
		data->statement = PLAY;
	else if (keycode == XK_Up)
	{
		if (data->menu.state_menu != RESUME)
			data->menu.state_menu--;
	}
	else if (keycode == XK_Down)
	{
		if (data->menu.state_menu != EXIT)
			data->menu.state_menu++;
	}
}
