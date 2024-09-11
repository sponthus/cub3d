/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: endoliam <endoliam@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 16:55:05 by sponthus          #+#    #+#             */
/*   Updated: 2024/09/10 23:14:48 by endoliam         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "cub3d.h"
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include "utils.h"

struct s_data;

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

void	init_data(struct s_data *data);

bool	is_empty(t_list *lst);
bool	prepare_element(t_list *lst);
bool	is_element(t_list *lst, char *id);


#endif