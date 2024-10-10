/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sponthus <sponthus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 12:33:44 by endoliam          #+#    #+#             */
/*   Updated: 2024/10/10 16:15:48 by sponthus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYCAST_H
#define RAYCAST_H

# include <math.h>

# include "cub3d.h"

struct s_data;
struct s_img;

typedef	struct s_time
{
	double					tv_sec;
	double					tv_usec;
} t_time;


typedef struct s_move
{
	double					posx;
	double					posy;
	double					posz;
	double					pitch;
	double					horizon;
	double						fov;
	double					dirx;
	double					diry;
	double					olddirx;
	double					olddiry;
	double					planex;
	double					planey;
	double					oldplanex;
	double					oldplaney;
	double					time;
	double					old_time;
	double					frame;
	double					ticktock;
	double					speed;
	double					movespeed;
	double					rotspeed;
	double					wallheight;
	double					initz;
	double 					jump_speed;
	double					gravity;
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
	int			linestart;
	int			drawstart;
	int			drawend;
	int			dir;
	
} t_raycast;

typedef struct s_shadow
{
	double		posx;
	double		posy;
	double		posz;
	double		pitch;
	double		sidedistx;
	double		sidedisty;
	double		deltadistx;
	double		deltadisty;
} t_shadow;


/*				game			*/
void		init_game(struct s_data  *data);
int			move(struct s_data  *data);
void		player_move(struct s_data *data, double dirx, double diry);
/*				display			*/
void		init_img(struct s_data* data);
void		destroy_img(struct s_data *data);
void		put_pixel_background(struct s_data *data, struct s_img *dis);

/*				math			*/
void		raycasting(struct s_data  *data);

/*				color 			*/
unsigned int calculate_shaded_color(unsigned int color, double distance);

/*				mlx_utils		*/
void		my_mlx_pixel_put(struct s_img *data, int x, int y, int color);

double	my_get_time(void);

#endif