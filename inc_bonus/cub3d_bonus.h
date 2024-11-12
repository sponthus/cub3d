/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sponthus <sponthus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 16:08:16 by sponthus          #+#    #+#             */
/*   Updated: 2024/11/12 10:07:12 by sponthus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_BONUS_H
# define CUB3D_BONUS_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <stdbool.h>
# include <stddef.h>

# include "game_bonus.h"
# include "hook_bonus.h"
# include "menu_bonus.h"
# include "display_bonus.h"
# include "animation_bonus.h"

# define WIN_HEIGHT 1020
# define WIN_WIDTH 1920

# define NORTH 1
# define SOUTH 2
# define WEST 3
# define EAST 4
# define DOOR 5

# define DOOR_MSG "Press O to open/close door"

// Colors to personalize according to your vibe
# define COL_BACK 0x000000
# define COL_EMPTY 0xFFFFFF
# define COL_DOOR 0x1034A6
# define COL_OPEN 0xAFEEEE
# define COL_PLAYER 0xFFE0
# define COL_CONT 0xFFE0
# define COL_MSG 0x0fdf9411
# define FPS_COLOR 0x0fdf9411
# define BLACK 0x000000

# define TILE_SIZE 7
# define MINIMAP_HEIGHT 200
# define MINIMAP_WIDTH 250

typedef enum e_statement
{
	PAUSE = 0,
	SETTING_MENU,
	PLAY,
	MENU
} t_statement;

typedef struct s_data
{
	void				*mlx;
	void				*win;
	int					win_height;
	int					win_width;
	char				**map;
	t_inc				sprites;
	t_move				player;
	t_display			display;
	t_keypress			key;
	t_statement			statement;
	t_menu				menu;
}	t_data;

int		main(int argc, char **argv);
int		parsing(char *path, t_data *data);
void	init_data(t_data *data);
void	free_data(t_data *data);
int		destroy_game(t_data *data, int exit_status);
bool	open_image(t_data *data, t_img *img, char *path);
void	draw_minimap(t_data *data);
void	doors(t_data *data);
void	doors_message(t_data *data);
int		write_err(char *error, char *target, char *obj, int errno);
int		map_length(struct s_data *data);
int		map_size(struct s_data *data);

# endif