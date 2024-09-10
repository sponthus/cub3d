/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sponthus <sponthus@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 16:45:13 by sponthus          #+#    #+#             */
/*   Updated: 2024/09/09 17:44:53 by sponthus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

bool	check_content(t_pars pars)
{
	(void)pars;
	return (true);
}

bool	is_valid_file(char *path)
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
	t_pars	pars;

	pars.file = NULL;
	pars.lst_file = NULL;
	if (is_valid_file(path) == false)
		return (write_error("invalid filename ", path), 1);
	pars.fd = open(path, O_RDONLY);
	if (pars.fd == -1)
		return (write_error("cound not open file ", path), 1);
	if (fill_file(&pars) != 0)
		return (write_error("malloc error", NULL), 1); // encore rien a free normalement
	close(pars.fd);
	ft_lstiter(pars.lst_file, write_elem); // to supp
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