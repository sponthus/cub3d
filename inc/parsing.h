/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sponthus <sponthus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 16:55:05 by sponthus          #+#    #+#             */
/*   Updated: 2024/10/31 14:36:54 by sponthus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "utils.h"
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

# define CHAR_MAP " \n\t\v\f\r01NSEW"
# define WHITESPACES " \n\t\v\f\r"

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