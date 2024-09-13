/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: endoliam <endoliam@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 16:08:16 by sponthus          #+#    #+#             */
/*   Updated: 2024/09/13 15:50:21 by endoliam         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <stdbool.h>

# include "parsing.h"
# include "utils.h"
# include "game.h"
# include "mlx.h"
# include "hook.h"

# define WIN_HEIGHT 800;
# define WIN_WIDTH 800;


typedef struct s_img
{
	void				*img;
	char				*addr;
	int					bpp;
	int					line_length;
	int					endian;
}	t_img;

typedef struct s_inc
{
	t_img				*no;
	t_img				*so;
	t_img				*ea;
	t_img				*we;
}	t_inc;
typedef struct s_display
{
	t_img				ptr1;
	t_img				ptr2;
} t_display;

typedef struct s_data
{
	void				*mlx;
	void				*win;
	int					win_height;
	int					win_width;
	char				**map;
	t_inc				*sprites;
	t_move				player;
	t_display			display;
	t_keypress			key;
}	t_data;

int		main(int argc, char **argv);
int		parsing(char *path, t_data *data);
void	init_data(t_data *data);

#endif