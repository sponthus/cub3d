/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sponthus <sponthus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 11:42:46 by endoliam          #+#    #+#             */
/*   Updated: 2024/10/03 10:23:44 by sponthus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

//void	superposition_img(t_img *background, t_img *face)
//{
//	unsigned int	color = 0;
//	int				x = 0;
//	int				y = 0;
//	int				index = 0;
//
//	while (y < 800)
//	{
//       x = 0;
//        while (x < 800)
//		{
//			index = y * background->ll + x * (background->bpp / 8);
//			color = *(unsigned int *)(face->addr + index);
//			if (color != 0)
//			    *(unsigned int *)(background->addr + index) = color;
//			x++;
//		}
//		y++;
//	}
//}

unsigned int calculate_shaded_color(unsigned int color, double distance)
{
    // Adjust shading factor (more subtle shading)
	//double max_distance = 11.0; // Maximum distance for shading effect
	double shading_factor;
	shading_factor = 1.0 / (1.0 + (distance * 0.07)); // Smoothly interpolate shading
	//if (shading_factor < 0.3) // 0.3 garantit que la couleur ne sera jamais complètement noire
	//	shading_factor = 0.3;
	unsigned int r = (color >> 16) & 0xFF;
	unsigned int g = (color >> 8) & 0xFF;
	unsigned int b = color & 0xFF;

	// Apply shading with a lower intensity
	r = (unsigned int)(r * shading_factor);
	g = (unsigned int)(g * shading_factor);
	b = (unsigned int)(b * shading_factor);

	// Ensure color values are within the valid range [0, 255]
	if (r > 255) r = 255;
	if (g > 255) g = 255;
	if (b > 255) b = 255;
	
	return (r << 16) | (g << 8) | b;
}