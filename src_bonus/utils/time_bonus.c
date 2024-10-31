/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sponthus <sponthus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 19:05:07 by endoliam          #+#    #+#             */
/*   Updated: 2024/10/31 15:44:47 by sponthus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"
#include "utils_bonus.h"

double	ft_atod(char *s)
{
	double	nbr;
	double	fraction;
	double	divisor;

	nbr = 0;
	fraction = 0;
	divisor = 1;
	while (*s != '.')
	{
		nbr = nbr * 10 + (*s - '0');
		s++;
	}
	s++;
	while (*s && *s != ' ')
	{
		fraction = fraction * 10 + *s - '0';
		divisor *= 10;
		s++;
	}
	fraction *= 1 / divisor;
	nbr += fraction;
	return (nbr);
}

double	milisecond(char *line)
{
	int		i;
	char	*tmp;

	i = 0;
	tmp = line;
	while (tmp[i] && tmp[i] != ' ')
		i++;
	i++;
	return (ft_atod(tmp + i) * 1000);
}

double	second(char *line)
{
	int		i;

	i = 0;
	while (line[i] != ' ')
		i++;
	line[i] = '\0';
	return (ft_atod(line));
}

void	ticktock(t_time *tv)
{
	int		fd;
	char	*line;

	fd = open("/proc/uptime", O_RDONLY, 0);
	if (fd < 0)
	{
		tv->tv_usec = 0;
		tv->tv_sec = 0;
		return ;
	}
	line = get_next_line(fd);
	tv->tv_usec = milisecond(line);
	tv->tv_sec = second(line) - (tv->tv_sec * 1000.0);
	free(line);
	close(fd);
	return ;
}

double	my_get_time(void)
{
	t_time				t;

	ft_memset(&t, 0, sizeof(t_time));
	ticktock(&t);
	return ((t.tv_sec * 1000 + (t.tv_usec)));
}
