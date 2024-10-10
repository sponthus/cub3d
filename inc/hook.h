/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: endoliam <endoliam@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 14:26:46 by endoliam          #+#    #+#             */
/*   Updated: 2024/10/02 14:06:03 by endoliam         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef HOOK_H
#define HOOK_H

# include <X11/keysym.h>

struct s_data;

typedef	struct s_keypress
{
	int		w;
	int		s;
	int		a;
	int		d;
	int		c;
	int		right;
	int		left;
	int		up;
	int		down;
	int		tab;
	int		esc;
	int		space;
}	t_keypress;

int	key_release(int keycode, struct s_data *data);
int	key_press(int keycode, struct s_data *data);
int mouse_hook(int x, int y, struct s_data *data);

#endif

