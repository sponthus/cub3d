/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sponthus <sponthus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 11:42:46 by endoliam          #+#    #+#             */
/*   Updated: 2024/10/17 11:15:59 by sponthus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

unsigned int	calculate_shaded_color(unsigned int color, double distance)
{
	double			shading_factor;
	unsigned int	r;
	unsigned int	g;
	unsigned int	b;

	shading_factor = 1.0 / (1.0 + (distance * 0.07));
	r = (color >> 16) & 0xFF;
	g = (color >> 8) & 0xFF;
	b = color & 0xFF;
	r = (unsigned int)(r * shading_factor);
	g = (unsigned int)(g * shading_factor);
	b = (unsigned int)(b * shading_factor);
	if (r > 255)
		r = 255;
	if (g > 255)
		g = 255;
	if (b > 255)
		b = 255;
	return ((r << 16) | (g << 8) | b);
}
