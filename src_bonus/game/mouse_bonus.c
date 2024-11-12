/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sponthus <sponthus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 14:35:36 by endoliam          #+#    #+#             */
/*   Updated: 2024/11/12 11:16:31 by sponthus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"
#include "mlx.h"

int	mouse_hook(int x, int y, t_data *data)
{
	double	dx;
	double	dy;

	dx = x - (data->win_width * 0.5);
	dy = y - (data->win_height * 0.5);
	if (dx != 0)
		cam_rotate(data, -dx * data->player.rotspeed, 'w');
	if (dy != 0)
		cam_rotate(data, dy * data->player.rotspeed, 'h');
	mlx_mouse_move(data->mlx, data->win, data->win_width * 0.5,
		data->win_height * 0.5);
	return (0);
}

void	mouse_setting(t_data *data)
{
	int		x;
	int		y;

	// mlx_mouse_hide(data->mlx, data->win);
	mlx_mouse_get_pos(data->mlx, data->win, &x, &y);
	mouse_hook(x, y, data);
}
