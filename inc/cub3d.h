/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sponthus <sponthus@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 16:08:16 by sponthus          #+#    #+#             */
/*   Updated: 2024/09/09 17:08:44 by sponthus         ###   ########.fr       */
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

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bpp;
	int		line_length;
	int		endian;
}	t_img;

typedef struct s_inc
{
	t_img	*no;
	t_img	*so;
	t_img	*ea;
	t_img	*we;
}	t_inc;

typedef struct s_data
{
	void	*mlx;
	void	*win;
	int		win_height;
	int		win_width;
	char	**map;
	t_inc	*sprites;
}	t_data;

int	parsing(char *path, t_data *data);

#endif