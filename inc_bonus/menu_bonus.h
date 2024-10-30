/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_bonus.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: endoliam <endoliam@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 21:23:47 by endoliam          #+#    #+#             */
/*   Updated: 2024/10/30 13:39:47 by endoliam         ###   ########lyon.fr   */
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
	COLOR_SKY = 1,
	COLOR_FLOOR,
	MOVESPEED,
	ROTSPEED
}	t_setting_state;

typedef struct s_menu
{
	struct s_anim		background;
	struct s_anim		setting;
	struct s_anim		resume;
	struct s_anim		exit;
	struct s_anim		icone;
	struct s_anim		speed;
	struct s_anim		cam;
	struct s_anim		color;
	t_menu_state		state_menu;
} t_menu;

void	init_menu(struct s_data *data);
void	pause_game(struct s_data *data);

#endif