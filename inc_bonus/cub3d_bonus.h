/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: endoliam <endoliam@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 16:08:16 by sponthus          #+#    #+#             */
/*   Updated: 2024/10/17 14:55:16 by endoliam         ###   ########lyon.fr   */
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


typedef enum	e_statement
{
	PAUSE = 0,
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
int		destroy_game(t_data *data);
bool	open_image(t_data *data, t_img *img, char *path);

#endif