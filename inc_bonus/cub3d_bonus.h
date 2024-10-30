/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sponthus <sponthus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 16:08:16 by sponthus          #+#    #+#             */
/*   Updated: 2024/10/30 10:43:09 by sponthus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_BONUS_H
# define CUB3D_BONUS_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <stdbool.h>

# include "parsing_bonus.h"
# include "utils_bonus.h"
# include "game_bonus.h"
# include "mlx.h"
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

# define TILE_SIZE 7
# define MINIMAP_HEIGHT data->win_height / 6
# define MINIMAP_WIDTH data->win_width / 6

typedef enum e_statement
{
	PAUSE = 0,
	PLAY,
	MENU
}	t_statement;

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

#endif