/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: endoliam <endoliam@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 19:05:07 by endoliam          #+#    #+#             */
/*   Updated: 2024/11/13 10:42:20 by endoliam         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"
#include "utils_bonus.h"
#include <sys/time.h>

double	my_get_time(void)
{
	struct timeval	t;

	if (gettimeofday(&t, NULL))
		return (0);
	return ((t.tv_sec) * 1000 + (t.tv_usec) / 1000);
}
