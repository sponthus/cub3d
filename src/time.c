/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sponthus <sponthus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 19:05:07 by endoliam          #+#    #+#             */
/*   Updated: 2024/09/23 14:24:39 by sponthus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double		ft_atod(char *s)
{
	double		nbr;
	double	fraction;
	double	divisor;

	nbr = 0;
	fraction = 0;
	divisor	= 1;
	if (!s)
		return (0);
	while ((*s == 32) || (*s >= 9 && *s <= 13))
		s++;
	while (*s != '.')
	{
		nbr = nbr *10 + (*s - '0');
		s++;
	}
	s++;
	while(*s && *s != ' ')
	{
		fraction = fraction * 10 + *s - '0';
		divisor *= 10;
		s++;
	}
	fraction /= divisor;
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
	if (tmp[i] == ' ')
		i++;
	return (ft_atod(tmp + i) * 1000);
}
double 	second(char *line)
{
	int		i;
	char	*tmp;

	i = 0;
	tmp = line;
	while (tmp[i] != ' ')
		i++;
	tmp[i] = '\0';
	return (ft_atod(tmp));
}

void	ticktock(t_time *tv)
{
	int		fd;
	char	*line;

	fd = open("/proc/uptime", O_RDONLY, 0);
	if (fd < 0)
		exit (42); // free and exit
	line = get_next_line(fd);
	//printf("poc time = %s\n", line);
	tv->tv_usec = milisecond(line);
	tv->tv_sec = second(line)  - (tv->tv_sec * 1000.0);
	//printf("atood sec = %f, usec = %f\n",tv->tv_sec,tv->tv_usec);
	free(line);
	close(fd);
}

double	my_get_time(void)
{
	t_time				t;

	ft_memset(&t, 0, sizeof(t_time));
	ticktock(&t);
	return ((t.tv_sec * 1000 + (t.tv_usec)));
}
