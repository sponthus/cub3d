/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sponthus <sponthus@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 16:45:13 by sponthus          #+#    #+#             */
/*   Updated: 2024/09/16 14:46:27 by sponthus         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_data(t_data *data)
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

bool	what_is_it(t_list *actual)
{
	if (is_empty(actual)) // Ajouter PEC !map
		return (true);
	if (handle_map_elements(actual) == false)
		return (false);
	if (actual->map == true)
		return (true);
	if (prepare_element(actual) == false)
		return (false);
	if (is_element(actual, "NO") == true)
		return (true);
	else if (is_element(actual, "SO") == true)
		return (true);
	else if (is_element(actual, "WE") == true)
		return (true);
	else if (is_element(actual, "EA") == true)
		return (true);
	else if (is_element(actual, "F") == true)
		return (true);
	else if (is_element(actual, "C") == true)
		return (true);
	else
		write_error("Not an expected element : ", actual->content); // ecrit ta propre erreur laisse pas remonter
	return (false);
}

bool	is_valid_file_content(t_pars *pars)
{
	t_list	*actual;

	actual = pars->lst_file;
	while (actual)
	{
		if (what_is_it(actual) == true)
		{
			if (actual->empty == false && determine_content(actual) != 0)
				return (false);
			if (fill_element(pars, actual) != 0)
				return (false); // check si double et met erreur specifique
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

void	write_elem(t_pars *pars) // to suppress 
{
	printf("no = %s\n", pars->no);
	printf("so = %s\n", pars->so);
	printf("we = %s\n", pars->ea);
	printf("ea = %s\n", pars->we);
	printf("floor = %s\n", pars->floor_color);
	printf("ceiling = %s\n", pars->ceiling_color);
}

void	init_parsing(t_pars *pars) // init pars values
{
	pars->no = NULL;
	pars->so = NULL;
	pars->we = NULL;
	pars->ea = NULL;
	pars->floor_color = NULL;
	pars->ceiling_color = NULL;
	pars->fd = -1;
	pars->file = NULL;
	pars->lst_file = NULL;
	printf("Pars structure initialized\n"); //
}

int	parsing(char *path, t_data *data)
{
	t_pars	pars; 

	init_parsing(&pars);
	if (is_valid_file_format(path) == false)
		return (write_error("Invalid filename ", path), 1);
	printf("valid file format\n"); //
	pars.fd = open(path, O_RDONLY);
	if (pars.fd == -1)
		return (write_error("Could not open file ", path), 1);
	printf("file open\n"); //
	if (fill_file(&pars) != 0)
		return (write_error("Malloc error", NULL), 1); // encore rien a free normalement
	printf("file filled\n");
	close(pars.fd);
	if (is_valid_file_content(&pars) == false)
		return (ft_lstclear(&pars.lst_file, free), 1);
	write_elem(&pars);
	(void)data;
	return (0);
}

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