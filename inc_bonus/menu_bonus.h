/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_bonus.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: endoliam <endoliam@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 21:23:47 by endoliam          #+#    #+#             */
/*   Updated: 2024/11/05 17:17:32 by endoliam         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef MENU_BONUS_H
# define MENU_BONUS_H

# include "cub3d_bonus.h"
# include "display_bonus.h"
# include "animation_bonus.h"

struct s_data;

typedef enum	e_menu_state
{
	RESUME = 0,
	SETTING,
	EXIT
} t_menu_state;

typedef enum	e_setting_state
{
	MOVESPEED = 0,
	ROTSPEED,
	COLOR_SKY,
	COLOR_FLOOR
}	t_setting_state;

typedef enum	e_color_state
{
	RED = 0,
	GREEN,
	BLUE
}	t_color_state;

typedef struct s_color
{
	int		r;
	int		g;
	int		b;
} t_color;

typedef struct s_setting
{
	struct s_anim		speed;
	struct s_anim		cam;
	struct s_anim		color;
	struct s_anim		barre;
	struct s_anim		*cursor;
	int					cursor_cam;
	int					cursor_speed;
	t_color				cursor_sky;
	t_color				cursor_floor;
	t_setting_state		setting_state;
	t_color_state		color_state;
	
} t_setting;

typedef struct s_menu
{
	struct s_anim		background;
	struct s_anim		setting;
	struct s_anim		resume;
	struct s_anim		exit;
	struct s_anim		icone;
	t_setting			setting_menu;
	t_menu_state		state_menu;
} t_menu;

void	init_menu(struct s_data *data);
void	pause_game(struct s_data *data);

#endif