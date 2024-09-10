/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: endoliam <endoliam@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 12:33:44 by endoliam          #+#    #+#             */
/*   Updated: 2024/09/10 23:38:36 by endoliam         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYCAST_H
#define RAYCAST_H

# include <math.h>

# include "cub3d.h"

struct s_data;

typedef struct s_move
{
	double		posx;
	double		posy;
	double		dirx;
	double		diry;
	double		olddirx;
	double		olddiry;
	double		planex;
	double		planey;
	double		oldplanex;
	double		oldplaney;
	double		time;
	double		old_time;
	double		frame;
	double		movespeed;
	double		rotspeed;
	double		ticktock;
	double		wallheight;
} t_move;

typedef struct s_raycast
{
	int			mapx;
	int			mapy;
	double		camx;
	double		sidedistx;
	double		sidedisty;
	double		deltadistx;
	double		deltadisty;
	int			stepx;
	int			stepy;
	double		raydirx;
	double		raydiry;
	double		perpwalldist;
	int			lineheight;
	int			drawstart;
	int			drawend;

} t_raycast;

typedef	struct s_keypress
{
	int		z;
	int		s;
	int		q;
	int		d;
	int		right;
	int		left;
	int		esc;
}	t_keypress;

void	init_game(struct s_data  *data);
int		move(struct s_data  *data);

#endif