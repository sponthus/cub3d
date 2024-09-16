/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sponthus <sponthus@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 16:55:05 by sponthus          #+#    #+#             */
/*   Updated: 2024/09/16 14:43:31 by sponthus         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "cub3d.h"
# include "utils.h"
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>

typedef struct s_pars
{
	int		fd;
	char 	**file;
	t_list	*lst_file;
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
	char	*floor_color;
	char	*ceiling_color;

}	t_pars;

int		determine_content(t_list *lst);
bool	is_empty(t_list *lst);
bool	prepare_element(t_list *lst);
bool	is_element(t_list *lst, char *id);
bool	is_map_element(t_list *lst);
bool	handle_map_elements(t_list *lst);
int	fill_element(t_pars *pars, t_list *actual);

int	fill_colors(t_pars *pars, t_list *actual);

#endif