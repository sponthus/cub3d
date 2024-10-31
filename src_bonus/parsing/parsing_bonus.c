/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sponthus <sponthus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 16:45:13 by sponthus          #+#    #+#             */
/*   Updated: 2024/10/31 15:39:14 by sponthus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"
#include "parsing_bonus.h"
#include "errors.h"

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

bool	is_valid_xpm_format(char *path)
{
	int	j;

	if (path == NULL)
		return (false);
	j = ft_strlen(path);
	if (j > 4 && path[j - 4] == '.' && path[j - 3] == 'x'
		&& path[j - 2] == 'p' && path[j - 1] == 'm')
		return (true);
	return (false);
}

bool	check_img_format(t_pars *pars)
{
	if (is_valid_xpm_format(pars->no) == false)
		return (write_err(EXP_XPM, pars->no, "NO", false));
	if (is_valid_xpm_format(pars->so) == false)
		return (write_err(EXP_XPM, pars->so, "SO", false));
	if (is_valid_xpm_format(pars->we) == false)
		return (write_err(EXP_XPM, pars->we, "WE", false));
	if (is_valid_xpm_format(pars->ea) == false)
		return (write_err(EXP_XPM, pars->ea, "EA", false));
	return (true);
}

bool	is_valid_cub_format(char *path)
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

	init_parsing(&pars);
	if (is_valid_cub_format(path) == false)
		return (write_err("Invalid filename ", path, NULL, 1));
	pars.fd = open(path, O_RDONLY);
	if (pars.fd == -1)
		return (write_err("Could not open file ", path, NULL, 1));
	if (fill_file(&pars) != 0)
		return (write_err(ERR_MALLOC, NULL, NULL, 1));
	close(pars.fd);
	if (fill_file_content(data, &pars) == false)
		return (ft_lstclear(&pars.lst_file, free), 1);
	if (is_valid_map(data) == false)
		return (ft_lstclear(&pars.lst_file, free), 1);
	if (valid_data(data, &pars) == false)
		return (ft_lstclear(&pars.lst_file, free), 1);
	if (check_img_format(&pars) == false)
		return (ft_lstclear(&pars.lst_file, free), 1);
	if (init_mlx(data, &pars) == false)
		return (ft_lstclear(&pars.lst_file, free), 1);
	ft_lstclear(&pars.lst_file, free);
	return (0);
}
