/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_bonus.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sponthus <sponthus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 21:58:00 by endoliam          #+#    #+#             */
/*   Updated: 2024/11/12 10:15:42 by sponthus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DISPLAY_BONUS_H
# define DISPLAY_BONUS_H

struct	s_data;

typedef struct s_img
{
	void				*img;
	char				*addr;
	int					bpp;
	int					ll;
	int					endian;
	int					width;
	int					height;
}	t_img;

typedef struct s_inc
{
	t_img				no;
	t_img				so;
	t_img				ea;
	t_img				we;
	t_img				sky;
	t_img				door;
	unsigned int		floor;
	unsigned int		ceiling;
}	t_inc;

typedef struct s_display
{
	t_img				ptr1;
	int					x;
	int					y;
}	t_display;

void	init_img(struct s_data *data);
void	destroy_img(struct s_data *data, int x, int y);

#endif