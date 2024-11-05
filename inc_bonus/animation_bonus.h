/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation_bonus.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: endoliam <endoliam@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 21:18:37 by endoliam          #+#    #+#             */
/*   Updated: 2024/11/05 15:22:05 by endoliam         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef ANIMATION_BONUS_H
# define ANIMATION_BONUS_H

# include "display_bonus.h"

# define RESUME_ANIMATION 0
# define SETTING_ANIMATION 1
# define EXIT_ANIMATION 2
# define ICONE_ANIMATION 3
# define SPEED_ANIMATION 4
# define CAM_ANIMATION 5
# define COLOR_ANIMATION 6
# define RED_ANIMATION 7
# define GREEN_ANIMATION 8
# define BLUE_ANIMATION 9

struct s_data;

typedef struct s_frame
{
	t_img					frame;
	int						index;
	struct s_frame			*next;
	struct s_frame			*prev;
} t_frame;

typedef struct s_anim
{
	t_frame					*anim;
	double					animspeed;
	int						x;
	int						y;
	double					scale_x;
	double					scale_y;
} t_anim;

void	init_animation(struct s_data *data, t_anim *element, char *prefix, int nb);
void	update_frame(struct s_data *data, t_anim *element, int v);

#endif