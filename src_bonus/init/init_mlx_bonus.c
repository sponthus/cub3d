/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: endoliam <endoliam@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 16:07:51 by sponthus          #+#    #+#             */
/*   Updated: 2024/10/30 23:22:03 by endoliam         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */


#include "cub3d_bonus.h"
#include "parsing_bonus.h"

bool	open_image(t_data *data, t_img *img, char *path)
{
	img->img = mlx_xpm_file_to_image(data->mlx, path,
			&img->width, &img->height);
	if (img->img == NULL)
		return (write_err(ERR_OP_TEX, path, NULL, false));
	img->addr = mlx_get_data_addr(img->img, &img->bpp, &img->ll, &img->endian);
	if (!img->addr)
		return (write_err(ERR_OP_TEX, path, NULL, false));
	return (true);
}

void	init_data(t_data *data)
{
	if (WIN_HEIGHT < 100 || WIN_WIDTH < 100)
	{
		write_err("Windows size is too small (expected > 100px)", NULL, NULL, 42);
		exit(EXIT_FAILURE);
	}
	data->win_height = WIN_HEIGHT;
	data->win_width = WIN_WIDTH;
	data->map = NULL;
	data->mlx = NULL;
	data->win = NULL;
}

void	init_parsing(t_pars *pars)
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

void	init_menu(t_data *data)
{
	init_animation(data, &data->menu.background, "inc_bonus/background/", 66);
	init_animation(data, &data->menu.setting, "inc_bonus/menu/setting/", 30);
	init_animation(data, &data->menu.resume, "inc_bonus/menu/resume/", 29);
	init_animation(data, &data->menu.exit, "inc_bonus/menu/exit/", 31);
	init_animation(data, &data->menu.icone, "inc_bonus/menu/icone/", 10);
	init_animation(data, &data->menu.setting_menu.cam, "inc_bonus/menu/cam/", 0);
	init_animation(data, &data->menu.setting_menu.speed, "inc_bonus/menu/speed/", 0);
	init_animation(data, &data->menu.setting_menu.color, "inc_bonus/menu/color/", 0);
	init_animation(data, &data->menu.setting_menu.barre, "inc_bonus/menu/barre_setting/", 0);
	init_animation(data, &data->menu.setting_menu.cursor, "inc_bonus/menu/cursor_setting/", 0);
	data->menu.resume.scale_x = data->win_width / 1920.0;
	data->menu.resume.scale_y = data->win_height / 1080.0;
	data->menu.resume.x = data->win_width  - data->win_width * 0.7;
	data->menu.resume.y = data->win_height  - data->win_height * 0.4;
	data->menu.setting.scale_x = data->menu.resume.scale_x;
	data->menu.setting.scale_y = data->menu.resume.scale_y;
	data->menu.setting.x = data->win_width  - data->win_width * 0.3;
	data->menu.setting.y = data->win_height  - data->win_height * 0.3;
	data->menu.exit.scale_x = data->menu.resume.scale_x;
	data->menu.exit.scale_y = data->menu.resume.scale_y;
	data->menu.exit.x = data->win_width  - data->win_width * 0.7;
	data->menu.exit.y = data->win_height  - data->win_height * 0.2;
	data->menu.background.x = 0;
	data->menu.background.y = data->win_height;
	data->menu.icone.scale_x = data->menu.resume.scale_x;
	data->menu.icone.scale_y = data->menu.resume.scale_y;
	data->menu.setting_menu.speed.scale_x = data->menu.resume.scale_x;
	data->menu.setting_menu.speed.scale_y = data->menu.resume.scale_y ;
	data->menu.setting_menu.speed.x = data->win_width;
	data->menu.setting_menu.speed.y = data->win_height  - data->win_height * 0.9;
	data->menu.setting_menu.cam.scale_x = data->menu.resume.scale_x;
	data->menu.setting_menu.cam.scale_y = data->menu.resume.scale_y ;
	data->menu.setting_menu.cam.x = data->win_width;
	data->menu.setting_menu.cam.y = data->menu.setting_menu.speed.y + 100;
	data->menu.setting_menu.color.scale_x = data->menu.resume.scale_x;
	data->menu.setting_menu.color.scale_y = data->menu.resume.scale_y ;
	data->menu.setting_menu.color.x = data->win_width;
	data->menu.setting_menu.color.y = data->menu.setting_menu.cam.y + 100;
	data->menu.setting_menu.cursor.scale_x = data->menu.resume.scale_x * 0.8;
	data->menu.setting_menu.cursor.scale_y = data->menu.resume.scale_y * 0.8;
	data->menu.setting_menu.barre.scale_x = data->menu.resume.scale_x * 0.8;
	data->menu.setting_menu.barre.scale_y = data->menu.resume.scale_y * 0.8;
	data->menu.setting_menu.cursor_speed = 0;
	data->menu.setting_menu.cursor_cam = 0;
}

bool	init_mlx(t_data *data, t_pars *pars)
{
	data->mlx = mlx_init();
	if (!data->mlx)
		return (write_err(ERR_INIT, NULL, "mlx", 1));
	data->win = mlx_new_window(data->mlx, data->win_width,
			data->win_height, "cub3d");
	if (!data->win)
		return (write_err(ERR_INIT, NULL, "window", 1));
	mlx_hook(data->win, 2, 1L << 0, key_press, data);
	mlx_hook(data->win, 3, 1L << 1, key_release, data);
	mlx_hook(data->win, 17, 0, destroy_game, data);
	if (open_image(data, &data->sprites.no, pars->no) == false)
		return (false);
	if (open_image(data, &data->sprites.so, pars->so) == false)
		return (false);
	if (open_image(data, &data->sprites.we, pars->we) == false)
		return (false);
	if (open_image(data, &data->sprites.ea, pars->ea) == false)
		return (false);
	if (open_image(data, &data->sprites.door, "textures/ananas.xpm") == false)
		return (false);
	init_game(data);
	init_menu(data);
	return (true);
}
