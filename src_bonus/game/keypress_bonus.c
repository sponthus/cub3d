/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keypress_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: endoliam <endoliam@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 14:26:21 by endoliam          #+#    #+#             */
/*   Updated: 2024/10/30 22:58:51 by endoliam         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */


#include "cub3d_bonus.h" 

void	set_keysit(t_data *data)
{
	if (data->player.posz == 0 && !data->key.space)
	{
		data->key.c = 1;
		data->player.posz = data->win_height / 4;
		data->player.movespeed = data->player.movespeed / 2;
	}
	else if (!data->key.space)
	{
		data->key.c = 0;
		data->player.posz = 0;
	}
}

void	set_keyjump(t_data *data)
{
	if (!data->key.space)
	{
		data->key.space = 1;
		data->player.jump_speed = -4;
		data->player.initz = data->player.posz;
	}
}

void	set_keyplayer(int keycode, t_data *data)
{
	if (keycode == XK_w)
		data->key.w = 1;
	if (keycode == XK_s)
		data->key.s = 1;
	if (keycode == XK_a)
		data->key.a = 1;
	if (keycode == XK_d)
		data->key.d = 1;
	if (keycode == XK_Shift_L)
		data->key.shift_l = 1;
	if (keycode == XK_o)
		doors(data);
}

void	set_keycam(int keycode, t_data *data)
{
	if (keycode == XK_Left)
		data->key.left = 1;
	if (keycode == XK_Right)
		data->key.right = 1;
	if (keycode == XK_Up)
		data->key.up = 1;
	if (keycode == XK_Down)
		data->key.down = 1;
	if (keycode == XK_c)
		set_keysit(data);
	if (keycode == XK_space)
		set_keyjump(data);
}

void	move_speed_cursor(int keycode, t_data *data)
{
	if (keycode == XK_Right)
	{
		if (data->player.movespeed <= 0.144)
		{
			data->menu.setting_menu.cursor_speed += 10;
			data->player.movespeed += 0.001;
		}
	}
	else if (keycode == XK_Left)
	{
		if (data->player.movespeed > 0.05)
		{
			data->menu.setting_menu.cursor_speed -= 10;
			data->player.movespeed -= 0.001;
		}
	}
}

void	move_cam_cursor(int keycode, t_data *data)
{
	if (keycode == XK_Right && data->player.rotspeed <= 0.0103)
	{
		data->menu.setting_menu.cursor_cam += 10;
		data->player.rotspeed += 0.0001;
	}
	else if (keycode == XK_Left && data->player.rotspeed > 0.00101)
	{
		data->menu.setting_menu.cursor_cam -= 10;
		data->player.rotspeed -= 0.0001;
	}
}

unsigned int	move_red(unsigned int color, int x)
{
	unsigned int		r = (color >> 16) & 0xFF;
	unsigned int		g = (color >> 8) & 0xFF;
	unsigned int		b = color & 0xFF;
	if (r + (unsigned int)x > 0 && r + (unsigned int)x <= 255)
		r += (unsigned int)x;
	return (r << 16 | g << 8 | b);
}

unsigned int	move_green(unsigned int color, int x)
{
	unsigned int		r = (color >> 16) & 0xFF;
	unsigned int		g = (color >> 8) & 0xFF;
	unsigned int		b = color & 0xFF;
	if (g + (unsigned int)x > 0 && g + (unsigned int)x <= 255)
		g += (unsigned int)x;
	return (r << 16 | g << 8 | b);
}

unsigned int	move_blue(unsigned int color, int x)
{
	unsigned int		r = (color >> 16) & 0xFF;
	unsigned int		g = (color >> 8) & 0xFF;
	unsigned int		b = color & 0xFF;
	if (b + (unsigned int)x > 0 && b + (unsigned int)x <= 255)
		b += (unsigned int)x;
	return (r << 16 | g << 8 | b);
}
void	down_color(t_data *data)
{
	if (data->menu.setting_menu.setting_state == COLOR_SKY)
	{
		if (data->menu.setting_menu.color_state == RED)
			data->sprites.ceiling = move_red(data->sprites.ceiling, -1);
		else if (data->menu.setting_menu.color_state == GREEN)
			data->sprites.ceiling = move_green(data->sprites.ceiling, -1);
		else
			data->sprites.ceiling = move_blue(data->sprites.ceiling, -1);
	}
	else
	{
		if (data->menu.setting_menu.color_state == RED)
			data->sprites.floor = move_red(data->sprites.floor, -1);
		else if (data->menu.setting_menu.color_state == GREEN)
			data->sprites.floor = move_green(data->sprites.floor, -1);
		else
			data->sprites.floor = move_blue(data->sprites.floor, -1);
	}
}
void	up_color(t_data *data)
{
	if (data->menu.setting_menu.setting_state == COLOR_SKY)
	{
		if (data->menu.setting_menu.color_state == RED)
			data->sprites.ceiling = move_red(data->sprites.ceiling, 1);
		else if (data->menu.setting_menu.color_state == GREEN)
			data->sprites.ceiling = move_green(data->sprites.ceiling, 1);
		else
			data->sprites.ceiling =move_blue(data->sprites.ceiling, 1);
	}
	else
	{
		if (data->menu.setting_menu.color_state == RED)
			data->sprites.floor = move_red(data->sprites.floor, 1);
		else if (data->menu.setting_menu.color_state == GREEN)
			data->sprites.floor = move_green(data->sprites.floor, 1);
		else
			data->sprites.floor = move_blue(data->sprites.floor, 1);
	}
}
void	move_color(int keycode, t_data *data)
{
	if (keycode == XK_Right)
		down_color(data);
	else if (keycode == XK_Left)
		up_color(data);
}
void	key_press_for_setting_menu(int keycode, t_data *data)
{
	if (keycode == XK_BackSpace)
	{
		data->menu.setting_menu.setting_state = MOVESPEED;
		data->statement = PAUSE;
	}
	else if (keycode == XK_Up)
	{
		if (data->menu.setting_menu.setting_state >= COLOR_SKY && data->menu.setting_menu.color_state != RED)
				data->menu.setting_menu.color_state--;
		else if (data->menu.setting_menu.setting_state != MOVESPEED)
			data->menu.setting_menu.setting_state--;
	}
	else if (keycode == XK_Down)
	{
		if (data->menu.setting_menu.setting_state >= COLOR_SKY && data->menu.setting_menu.color_state != BLUE)
				data->menu.setting_menu.color_state++;
		else if (data->menu.setting_menu.setting_state != COLOR_FLOOR)
			data->menu.setting_menu.setting_state++;
	}
	else if (data->menu.setting_menu.setting_state == MOVESPEED)
		move_speed_cursor(keycode, data);
	else if (data->menu.setting_menu.setting_state == ROTSPEED)
		move_cam_cursor(keycode, data);
	else if (data->menu.setting_menu.setting_state == COLOR_SKY
		|| data->menu.setting_menu.setting_state == COLOR_FLOOR)
		move_color(keycode, data);
	//else if (data->menu.setting_menu.setting_state == COLOR_FLOOR)
	//	move_color_floor(keycode, data);
}

int	key_press(int keycode, t_data *data)
{
	if (keycode == XK_Escape)
		destroy_game(data, EXIT_SUCCESS);
	else if (keycode == XK_Tab)
	{
		if (data->statement == PLAY)
			data->statement = PAUSE;
		else if (data->statement == PAUSE)
			data->statement = PLAY;
	}
	else if (data->statement == PLAY)
	{
		set_keyplayer(keycode, data);
		set_keycam(keycode, data);
	}
	else if (data->statement == PAUSE)
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
	else if (data->statement == SETTING_MENU)
	{
		key_press_for_setting_menu(keycode, data);
	}
	return (0);
}
