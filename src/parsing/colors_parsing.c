/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_data.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sponthus <sponthus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 13:41:06 by sponthus          #+#    #+#             */
/*   Updated: 2024/09/19 14:54:01 by sponthus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "parsing.h"
#include "errors.h"

bool	check_rgb(char **rgb, char *color)
{
	int	r;
	int	g;
	int	b;

	r = 0;
	g = 0;
	b = 0;
	if (rgb[0])
		r = color_atou(rgb[0]);
	else
		return (write_err(ERR_MIS_RGB, "R", NULL, false));
	if (rgb[1])
		g = color_atou(rgb[1]);
	else
		return (write_err(ERR_MIS_RGB, "G", NULL, false));
	if (rgb[2])
		b = color_atou(rgb[2]);
	else
		return (write_err(ERR_MIS_RGB, "B", NULL, false));
	if (rgb[3])
		return (write_err(ERR_RGB_ONL, color, NULL, false));
	if (r > 255 || g > 255 || b > 255)
		return (write_err(ERR_RGB_RAN, color, NULL, false));
	return (true);
}

bool	char_to_color(t_data *data, char *color, char *what)
{
	char	**rgb;
	int		r;
	int		g;
	int		b;

	r = 0;
	g = 0;
	b = 0;
	rgb = ft_split(color, ',');
	if (rgb == NULL)
		return (write_err(ERR_MALLOC, "color", NULL, false));
	if (check_rgb(rgb, color) == false)
	{
		free_full_split(rgb);
		return (false);
	}
	r = color_atou(rgb[0]);
	g = color_atou(rgb[1]);
	b = color_atou(rgb[2]);
	if (ft_strncmp(what, "floor", 5) == 0)
		data->sprites.floor = (r << 16 | g << 8 | b);
	else
		data->sprites.ceiling = (r << 16 | g << 8 | b);
	free_full_split(rgb);
	return (true);
}

bool	valid_color(char *color)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (color[i])
	{
		if (color[i] == '\n')
		{
			color[i] = '\0';
			break ;
		}
		if ((color[i] != ',') && ft_isdigit(color[i]) == 0)
			return (write_err(ERR_RGB_RAN, color, NULL, false));
		if (color[i] == ',')
			count++;
		i++;
	}
	if (count != 2)
		return (write_err(ERR_RGB_RAN, color, NULL, false));
	return (true);
}

bool	valid_data(t_data *data, t_pars *pars)
{
	if (!pars->floor_color)
		return (write_err(ERR_MIS_COL, "F", NULL, false));
	if (!pars->ceiling_color)
		return (write_err(ERR_MIS_COL, "C", NULL, false));
	if (valid_color(pars->floor_color) == false
		|| char_to_color(data, pars->floor_color, "floor") == false)
		return (false);
	if (valid_color(pars->ceiling_color) == false
		|| char_to_color(data, pars->ceiling_color, "ceiling") == false)
		return (false);
	if (!pars->no)
		return (write_err(ERR_MIS_TEX, "NO", NULL, false));
	if (!pars->so)
		return (write_err(ERR_MIS_TEX, "SO", NULL, false));
	if (!pars->we)
		return (write_err(ERR_MIS_TEX, "WE", NULL, false));
	if (!pars->ea)
		return (write_err(ERR_MIS_TEX, "EA", NULL, false));
	return (true);
}
