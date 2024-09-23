/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sponthus <sponthus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 16:55:05 by sponthus          #+#    #+#             */
/*   Updated: 2024/09/23 13:45:45 by sponthus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "cub3d.h"
# include "utils.h"
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>

struct s_data;

typedef struct s_pars
{
	int		fd;
	char	**file;
	t_list	*lst_file;
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
	char	*floor_color;
	char	*ceiling_color;

}	t_pars;


# define ERR_MALLOC "Malloc error"
# define ERR_MIS_COL "Missing color"
# define ERR_MIS_TEX "Missing texture"
# define ERR_RGB_ONL "Color should contain only R,G,B"
# define ERR_RGB_RAN "Color RGB shoud contain 0 to 255"
# define ERR_RGB_FOR "Color should be in R,G,B format"
# define ERR_MIS_RGB "Color contains no "
# define ERR_RED "Redefined"
# define ERR_INIT "Failed to init"
# define ERR_NO_ELEM "Element missing"

int		resize_content(t_list *lst);
bool	is_empty(t_list *lst);
bool	prepare_element(t_list *lst);
bool	is_element(t_list *lst, char *id);

bool	is_map_element(t_list *lst);
bool	handle_map_elements(t_list *lst);
int		list_map_size(t_list *lst);
void	replace_whitespaces(char *str);
bool	empty_mapline(char *str);

bool	what_is_it(t_list *actual);

int	fill_element(t_pars *pars, t_list *actual);

int	fill_colors(t_pars *pars, t_list *actual);
int	fill_ea(t_pars *pars, t_list *actual);
int	fill_we(t_pars *pars, t_list *actual);
int	fill_so(t_pars *pars, t_list *actual);
int	fill_no(t_pars *pars, t_list *actual);

bool	init_mlx(struct s_data *data, t_pars *pars);
bool	valid_data(struct s_data *data, t_pars *pars);
bool	fill_file_content(struct s_data *data, t_pars *pars);

int	map_length(struct s_data *data);
int	map_size(struct s_data *data);

bool	valid_color(char *floor_color);

int		fill_map(struct s_data *data, t_list *actual);
bool	is_valid_map(struct s_data *data);
bool	char_to_color(struct s_data *data, char *color, char *what);

#endif