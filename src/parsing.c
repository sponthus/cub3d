/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: endoliam <endoliam@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 16:45:13 by sponthus          #+#    #+#             */
/*   Updated: 2024/09/11 00:06:38 by endoliam         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*void	init_data(t_data *data)
{
	data->win_height = WIN_HEIGHT;
	data->win_width = WIN_WIDTH;
	data->map = NULL;
	data->sprites = NULL;
}

int	fill_file(t_pars *pars)
{
	char	*line;
	t_list	*tmp;

	line = get_next_line(pars->fd);
	if (line)
	{
		pars->lst_file = ft_lstnew(line);
		if (!pars->lst_file)
			return (free(line), 1);
	}
	while (pars->lst_file && line)
	{
		line = get_next_line(pars->fd);
		if (line)
		{
			tmp = ft_lstnew(line);
			ft_lstadd_back(&pars->lst_file, tmp);
			if (!tmp)
			{
				ft_lstclear(&pars->lst_file, free);
				return (free(line), 1);
			}
		}
	}
	return (0);
}

bool	what_is_it(t_pars *pars, t_list *actual)
{
	if (is_empty(actual) == true) // actual == NULL || actual->size == 1 + whitespqces
		return (true);
	if (is_element(actual, "NO") == true)
		pars->no = ft_strdup(actual->content); // ou fonction fill element qui check si double et met erreur specifique
	else if (is_element(actual, "SO") == true)
		pars->so = ft_strdup(actual->content);
	else if (is_element(actual, "WE") == true)
		pars->we = ft_strdup(actual->content);
	else if (is_element(actual, "EA") == true)
		pars->ea = ft_strdup(actual->content);
	else if (is_element(actual, "F") == true)
		pars->floor_color = ft_strdup(actual->content);
	else if (is_element(actual, "C") == true)
		pars->floor_color = ft_strdup(actual->content);
	else if (is_map(actual) == true)
		(void)pars; // determner comment faire
	return (false); // add msg erreur
}

bool	is_valid_file_content(t_data *data, t_pars *pars)
{
	// t_list	*prev;
	t_list	*actual;

	// prev = NULL;
	actual = pars->lst_file;
	while (actual)
	{
		if (what_is_it(actual, data) == true)
		{
			// prev = actual;
			actual = actual->next;
		}
		else
			return (false);
	}
	return (true);
}

bool	is_valid_file_format(char *path)
{
	int	j;

	if (path == NULL)
		return (false);
	j = ft_strlen(path);
	if (j > 4 && path[j - 4] == '.' && path[j - 3] == 'c'
		&& path[j - 2] == 'u' && path[j - 1] == 'b')
		return (true);
	return (false);
}

void	write_elem(void *ptr) // to suppress 
{
	if (write(1, ptr, ft_strlen(ptr)) == -1)
		return ;
}

int	parsing(char *path, t_data *data)
{
	t_pars	pars; // init valeurs de pars

	if (is_valid_file_format(path) == false)
		return (write_error("Invalid filename ", path), 1);
	pars.fd = open(path, O_RDONLY);
	if (pars.fd == -1)
		return (write_error("Cound not open file ", path), 1);
	if (fill_file(&pars) != 0)
		return (write_error("Malloc error", NULL), 1); // encore rien a free normalement
	close(pars.fd);
	ft_lstiter(pars.lst_file, write_elem); // to supp
	// if (is_valid_file_content(data, pars) == false)
	// 	return (ft_lstclear(&pars.lst_file, free), 1);
	(void)data;
	return (0);
} */

/*
	t_data	data;

	if (argc == 2)
	{
		if (parsing(argv[1], &data) == 1)
			return (1);
	}
	else if (argc == 1)
	{
		if (parsing("inc/default.cub", &data) == 1)
			return (1);
	}
	else
		return (1);
*/