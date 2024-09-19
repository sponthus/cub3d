/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_elements.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sponthus <sponthus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 13:41:06 by sponthus          #+#    #+#             */
/*   Updated: 2024/09/19 14:54:01 by sponthus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	check_rgb(char **rgb, char *color)
{
	int	r;
	int	g;
	int	b;
	
	r = 0;
	g = 0;
	b = 0;
	if (rgb[0])
		r = color_atoi(rgb[0]);
	else
		return (write_error("Color contains no R", NULL, false));
	if (rgb[1])
		g = color_atoi(rgb[1]);
	else
		return (write_error("Color contains no G", NULL, false));
	if (rgb[2])
		b = color_atoi(rgb[1]);
	else
		return (write_error("Color contains no B", NULL, false));
	if (rgb[3])
		return (write_error("Color should contain only R,G,B", color, false));
	if (r > 255 || g > 255 || b > 255)
	{
		printf("r = %d, g = %d, b = %d\n", r, g, b);
		return (write_error("Color RGB shoud contain 0 to 255", color, false));
	}
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
		return (write_error("Malloc error", "color", false));
	if (check_rgb(rgb, color) == false)
	{
		free_full_split(rgb);
		return (false);
	}
	r = color_atoi(rgb[0]);
	g = color_atoi(rgb[1]);
	b = color_atoi(rgb[2]);
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
		if (color[i] != ',' && ft_isdigit(color[i]) == 0)
		{
			return (write_error("Color RGB shoud contain 0 to 255", color, false));
		}
		if (color[i] == ',')
			count++;
		i++;
	}
	if (count != 2)
		return (write_error("Color should be in R,G,B format", color, false));
	return (true);
}
