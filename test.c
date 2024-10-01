// exemple de comment stocker tous les pixels des textures

// static int	*xpm_to_img(t_data *data, char *path)
// {
// 	t_img	tmp;
// 	int		*buffer;
// 	int		x;
// 	int		y;

// 	init_texture_img(data, &tmp, path);
// 	buffer = ft_calloc(1,
// 			sizeof * buffer * data->texinfo.size * data->texinfo.size);
// 	if (!buffer)
// 		clean_exit(data, err_msg(NULL, ERR_MALLOC, 1));
// 	y = 0;
// 	while (y < data->texinfo.size)
// 	{
// 		x = 0;
// 		while (x < data->texinfo.size)
// 		{
// 			buffer[y * data->texinfo.size + x]
// 				= tmp.addr[y * data->texinfo.size + x];
// 			++x;
// 		}
// 		y++;
// 	}
// 	mlx_destroy_image(data->mlx, tmp.img);
// 	return (buffer);
// }

// Exemple de comment calculer les pixels
// void	update_texture_pixels(t_data *data, t_texinfo *tex, t_ray *ray, int x)
// {
// 	int			y;
// 	int			color;

// 	get_texture_index(data, ray); // choisir tex->index a NORTH ... 
// 	tex->x = (int)(ray->wall_x * tex->size);
// 	if ((ray->side == 0 && ray->dir_x < 0)
// 		|| (ray->side == 1 && ray->dir_y > 0))
// 		tex->x = tex->size - tex->x - 1;
// 	tex->step = 1.0 * tex->size / ray->line_height;
// 	tex->pos = (ray->draw_start - data->win_height / 2
// 			+ ray->line_height / 2) * tex->step;
// 	y = ray->draw_start;
// 	while (y < ray->draw_end)
// 	{
// 		tex->y = (int)tex->pos & (tex->size - 1);
// 		tex->pos += tex->step;
// 		color = data->textures[tex->index][tex->size * tex->y + tex->x];
// 		if (tex->index == NORTH || tex->index == EAST)
// 			color = (color >> 1) & 8355711;
// 		if (color > 0)
// 			data->texture_pixels[y][x] = color;
// 		y++;
// 	}
// }
