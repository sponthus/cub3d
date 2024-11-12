/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_bonus.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sponthus <sponthus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 12:33:44 by endoliam          #+#    #+#             */
/*   Updated: 2024/11/12 10:17:35 by sponthus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GAME_BONUS_H
# define GAME_BONUS_H

# include <math.h>
# include "cub3d_bonus.h"

struct	s_data;
struct	s_img;

typedef struct s_time
{
	double					tv_sec;
	double					tv_usec;
}	t_time;

typedef struct s_move
{
	double					posx;
	double					posy;
	double					posz;
	double					pitch;
	double					horizon;
	double					fov;
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
	double					movespeed;
	double					speed;
	double					rotspeed;
	double					wallheight;
	double					initz;
	double					jump_speed;
	double					gravity;
	int						size_mapx;
	int						size_mapy;
	bool					sprint;
}	t_move;

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
	int			door;
}	t_raycast;

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
}	t_shadow;

/*				game			*/
void			init_game(struct s_data *data);
void			move(struct s_data *data);
void			player_move(struct s_data *data, double dirx, double diry);
void			cam_rotate(struct s_data *data, double rotspeed, int flag);
void			mouse_setting(struct s_data *data);

/*					display			*/
void			put_pixel_background(struct s_data *data, struct s_img *dis);
void			draw_line(struct s_data *data, t_raycast *ray, int x, int side);
int				display_game(struct s_data *data);

/*					math			*/
void			raycasting(struct s_data *data);

/*					textures		*/
int				calc_texx_x(struct s_data *data, t_raycast *ray);
int				calc_texx_y(struct s_data *data, t_raycast *ray);
int				chose_dir(int side, t_raycast *ray);
int				tex_chose_color(struct s_data *data, int x, int y, int dir);
int				tex_find_color(struct s_img *img, int y, int x);

/*				color 			*/
unsigned int	calculate_shaded_color(unsigned int color, double distance);

/*				mlx_utils		*/
void			my_mlx_pixel_put(struct s_img *data, int x, int y, int color);
void			update_frame_data(struct s_data *data);
double			my_get_time(void);
char			*ft_itoa(int n);

#endif