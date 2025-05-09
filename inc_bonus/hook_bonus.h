/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_bonus.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sponthus <sponthus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 14:26:46 by endoliam          #+#    #+#             */
/*   Updated: 2024/11/12 10:18:02 by sponthus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HOOK_BONUS_H
# define HOOK_BONUS_H

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
	int		enter;
}	t_keypress;

int		key_release(int keycode, struct s_data *data);
int		key_press(int keycode, struct s_data *data);
int		mouse_hook(int x, int y, struct s_data *data);
void	key_press_for_setting_menu(int keycode, struct s_data *data);
void	key_press_for_menu(int keycode, struct s_data *data);
void	keypress_move_color(int keycode, struct s_data *data);

void	find_keyplayer_move(struct s_data *data);
void	find_keyaction(struct s_data *data);
void	find_keycam_move(struct s_data *data);

#endif
