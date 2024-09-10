/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: endoliam <endoliam@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 12:33:44 by endoliam          #+#    #+#             */
/*   Updated: 2024/09/10 16:59:15 by endoliam         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYCAST_H
#define RAYCAST_H

# include <math.h>

# include "cub3d.h"

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


#endif