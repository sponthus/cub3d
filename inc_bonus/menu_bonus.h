/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_bonus.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: endoliam <endoliam@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 21:23:47 by endoliam          #+#    #+#             */
/*   Updated: 2024/11/08 14:02:57 by endoliam         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef MENU_BONUS_H
# define MENU_BONUS_H

# include "cub3d_bonus.h"
# include "display_bonus.h"
# include "animation_bonus.h"

# define MEN_BACK "inc_bonus/background/"
# define MEN_SET "inc_bonus/menu/setting/"
# define MEN_RES "inc_bonus/menu/resume/"
# define MEN_EXI  "inc_bonus/menu/exit/"
# define MEN_IC "inc_bonus/menu/icone/"
# define MEN_CAM "inc_bonus/menu/cam/"
# define MEN_SPEED "inc_bonus/menu/speed/"
# define MEN_COLOR "inc_bonus/menu/color/"
# define MEN_BAR "inc_bonus/menu/barre_setting/"

# define SCALE_X WIN_WIDTH / 1920.0
# define SCALE_Y WIN_HEIGHT / 700.0

# define MAX_SPEED 0.144
# define MIN_SPEED 0.05
# define MAX_ROT 0.0103
# define MIN_ROT  0.00101

# define MEN_FLAG 1
# define SETTI_FLAG 2

struct s_data;

typedef enum e_menu_state
{
	RESUME = 0,
	SETTING,
	EXIT
}	t_menu_state;

typedef enum e_setting_state
{
	MOVESPEED = 0,
	ROTSPEED,
	COLOR_SKY,
	COLOR_FLOOR
}	t_setting_state;

typedef enum e_color_state
{
	RED = 0,
	GREEN,
	BLUE
}	t_color_state;

typedef struct s_color_cursor
{
	int		r;
	int		g;
	int		b;
}	t_color_cursor;

typedef struct s_setting
{
	struct s_anim				speed;
	struct s_anim				cam;
	struct s_anim				color;
	struct s_anim				barre;
	struct s_anim				*cursor;
	int							cursor_cam;
	int							cursor_speed;
	t_color_cursor				cursor_sky;
	t_color_cursor				cursor_floor;
	t_setting_state				setting_state;
	t_color_state				color_state;
}	t_setting;

typedef struct s_menu
{
	struct s_anim				background;
	struct s_anim				setting;
	struct s_anim				resume;
	struct s_anim				exit;
	struct s_anim				icone;
	t_setting					setting_menu;
	t_menu_state				state_menu;
}	t_menu;

void	init_menu(struct s_data *data);
void	pause_game(struct s_data *data);
void	setting_menu(struct s_data *data);

void	put_cursor(struct s_data *data, int flag, t_color_cursor *c_cursor);
void	put_line(struct s_data *data, int basex, int basey, int cursor);
void	put_button(struct s_data *data, t_anim *element, int flag);
void	put_background(struct s_data *data, t_anim *element);

#endif