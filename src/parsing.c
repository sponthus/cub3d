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
	int		i;

	i = 0;
	line = get_next_line(pars->fd);
	while (line)
	{
		// ajouter maillons de la chaine de lignes au fur et a mesure
	}
}

bool	check_content(t_pars pars)
{

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

int	parsing(char *path, t_data *data)
{
	t_pars	pars;

	pars.file = NULL;
	if (is_valid_file(path) == false)
		return (write_error("invalid filename ", path), 1);
	pars.fd = open(path, O_RDONLY);
	if (pars.fd == -1)
	{
		write_error("cound not open file ", path);
		return (1);
	}
	close(pars.fd);
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