/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sponthus <sponthus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 14:26:46 by endoliam          #+#    #+#             */
/*   Updated: 2024/10/31 14:29:27 by sponthus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HOOK_H
# define HOOK_H

# include <X11/keysym.h>

struct	s_data;

typedef struct s_keypress
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
	int		shift_l;
	int		esc;
	int		space;
	int		tab;
}	t_keypress;

int		key_release(int keycode, struct s_data *data);
int		key_press(int keycode, struct s_data *data);
int		mouse_hook(int x, int y, struct s_data *data);

#endif
