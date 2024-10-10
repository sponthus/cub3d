/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sponthus <sponthus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 16:45:13 by sponthus          #+#    #+#             */
/*   Updated: 2024/10/09 16:58:02 by sponthus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_data(t_data *data)
{
	data->win_height = WIN_HEIGHT;
	data->win_width = WIN_WIDTH;
	data->map = NULL;
	data->mlx = NULL;
	data->win = NULL;
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

void	write_elem(t_data *data, t_pars *pars) // to suppress 
{
	int	i;

	i = 0;
	printf("no = %s\n", pars->no);
	printf("so = %s\n", pars->so);
	printf("we = %s\n", pars->ea);
	printf("ea = %s\n", pars->we);
	printf("floor = %s\n", pars->floor_color);
	printf("ceiling = %s\n", pars->ceiling_color);
	while (data->map && data->map[i])
	{
		if (data->map[i])
			printf("/%s/\n", data->map[i]);
		i++;
	}
	printf("RGB floor color registered is : ");
	printf("%d - %d - %d\n", ((data->sprites.floor >> 16) & 0xFF), ((data->sprites.floor >> 8) & 0xFF), (data->sprites.floor & 0xFF));
	printf("RGB ceiling color registered is : ");
	printf("%d - %d - %d\n", ((data->sprites.ceiling >> 16) & 0xFF), ((data->sprites.ceiling >> 8) & 0xFF), (data->sprites.ceiling & 0xFF));
}

int	parsing(char *path, t_data *data)
{
	t_pars	pars;

	init_parsing(&pars);
	if (is_valid_file_format(path) == false)
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
	printf("entering init mlx \n");
	if (init_mlx(data, &pars) == false)
		return (ft_lstclear(&pars.lst_file, free), 1);
	// write_elem(data, &pars); //
	ft_lstclear(&pars.lst_file, free);
	return (0);
}
