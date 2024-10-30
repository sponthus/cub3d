/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_bonus.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sponthus <sponthus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 16:55:05 by sponthus          #+#    #+#             */
/*   Updated: 2024/10/30 12:30:54 by sponthus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_BONUS_H
# define PARSING_BONUS_H

# include "cub3d_bonus.h"
# include "utils_bonus.h"
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>

struct	s_data;

typedef struct s_pars
{
	int		fd;
	char	**file;
	t_list	*lst_file;
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
	int		size;
	char	*floor_color;
	char	*ceiling_color;

}	t_pars;

# define ERR_COUNT "Wrong count"
# define EXP_1 "1 expected"
# define EXP_CUB "expected only file.cub"
# define EXP_XPM "expected only file.xpm"
# define ERR_MALLOC "Malloc error"
# define ERR_MIS_COL "Missing color"
# define ERR_MIS_TEX "Missing texture"
# define ERR_OP_TEX "Could not open texture"
# define ERR_RGB_ONL "Color should contain only R,G,B"
# define ERR_RGB_RAN "Color RGB shoud contain 0 to 255 in R,G,B format"
# define ERR_MIS_RGB "Color contains no "
# define ERR_RED "Redefined"
# define ERR_INIT "Failed to init"
# define ERR_NO_ELEM "Element missing"
# define ERR_UNEX "Unexpected element found"

# define CHAR_MAP " \n\t\v\f\r01NSEWD"

// PARSING
void	init_data(struct s_data *data);
void	init_parsing(t_pars *pars);
int		fill_file(t_pars *pars);
bool	is_valid_cub_format(char *path);
int		parsing(char *path, struct s_data *data);

// WHAT_IS_IT
bool	what_is_it(t_list *actual);
bool	is_element(t_list *lst, char *id);
bool	prepare_element(t_list *lst);
bool	is_empty(t_list *lst);
int		resize_content(t_list *lst);

// MAP_IS_VALID
bool	only_one_map(struct s_data *data);
bool	only_one_player(struct s_data *data);
bool	closed_map(struct s_data *data, int map_size);
bool	is_valid_map(struct s_data *data);

// MAP_MEASURE
int		map_length(struct s_data *data);
int		map_size(struct s_data *data);
int		list_map_size(t_list *lst);

// MAP_RECOGNIZE
bool	empty_mapline(char *str);
bool	is_map_element(t_list *lst);
void	replace_whitespaces(char *str);
bool	handle_map_elements(t_list *lst);

// FILL
bool	fill_file_content(struct s_data *data, t_pars *pars);
int		fill_element(t_pars *pars, t_list *actual);
int		fill_map(struct s_data *data, t_list *actual);
void	copy_map(char *dst, char *src);
int		resize_map(struct s_data *data);

// FILL_ELEMENTS
int		fill_colors(t_pars *pars, t_list *actual);
int		fill_ea(t_pars *pars, t_list *actual);
int		fill_we(t_pars *pars, t_list *actual);
int		fill_so(t_pars *pars, t_list *actual);
int		fill_no(t_pars *pars, t_list *actual);

// COLOR PARSING
bool	check_rgb(char **rgb, char *color);
bool	char_to_color(struct s_data *data, char *color, char *what);
bool	valid_color(char *color);
bool	valid_data(struct s_data *data, t_pars *pars);

// INIT_MLX
bool	init_mlx(struct s_data *data, t_pars *pars);

#endif