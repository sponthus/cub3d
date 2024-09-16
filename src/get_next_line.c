/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sponthus <sponthus@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 12:53:03 by sponthus          #+#    #+#             */
/*   Updated: 2024/09/16 12:53:04 by sponthus         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

int	read_file(int fd, char *buf)
{
	int	size;

	size = read(fd, buf, BUFFER_SIZE);
	if (size < 0)
	{
		return (-1);
	}
	buf[size] = '\0';
	return (size);
}

void	*ft_buffmove(char *dest, char *src, size_t size, int *n)
{
	size_t	i;

	i = 0;
	if (*n == 0)
	{
		while (i++ < BUFFER_SIZE + 1)
			*dest++ = '\0';
	}
	else
	{
		while (size-- > 0)
			*dest++ = *src++;
		*dest = '\0';
	}
	return (dest);
}

char	*ft_strlcpy_nl(char *str, char *s, int len, int *n)
{
	int	i;

	i = 0;
	if (s == NULL)
		return (str);
	while (s[i] && s[i] != '\n')
	{
		str[len + i] = s[i];
		i++;
	}
	if (s[i] == '\n')
	{
		str[len + i] = s[i];
		*n = i + 1;
		i++;
	}
	str[len + i] = '\0';
	return (str);
}

char	*ft_strjoin_free(char *s1, char *s2, int *n, int size)
{
	char	*str;
	size_t	lens1;

	if (!s1 && !s2)
		return (NULL);
	str = NULL;
	if (s2 == NULL)
		return (s1);
	lens1 = ft_strlen(s1);
	str = malloc(sizeof (char) * (lens1 + size + 1));
	if (str)
	{
		str = ft_strlcpy_nl(str, s1, 0, n);
		str = ft_strlcpy_nl(str, s2, lens1, n);
	}
	if (s1 != NULL)
		free(s1);
	return (str);
}

char	*read_while(int fd, char *buf, char *line, int *n)
{
	int	size;

	size = read_file(fd, buf);
	while (size > 0 && *n == 0)
	{
		line = ft_strjoin_free(line, buf, n, size);
		if (line == NULL)
			return (NULL);
		if (size > 0 && *n == 0)
			size = read_file(fd, buf);
	}
	if (size < 0)
	{
		if (line != NULL)
			free(line);
		*n = 0;
		return (NULL);
	}
	return (line);
}

char	*ft_cut(char *line, int *n)
{
	int		size;
	char	*new;

	if (line == NULL)
		return (NULL);
	size = ft_strlen(line);
	new = malloc(size + 1);
	if (new)
	{
		ft_strlcpy_nl(new, line, 0, n);
	}
	if (line)
		free(line);
	return (new);
}

char	*get_next_line(int fd)
{
	static char	buf[BUFFER_SIZE + 1] = "\0";
	char		*line;
	int			n;

	if (fd < 0 || BUFFER_SIZE <= 0)
	{
		buf[0] = '\0';
		return (NULL);
	}
	n = 0;
	line = NULL;
	if (buf[0] != '\0')
	{
		line = ft_strjoin_free(line, buf, &n, ft_strlen(buf));
		if (line == NULL)
			return (NULL);
	}
	if (n == 0)
		line = read_while(fd, buf, line, &n);
	ft_buffmove(buf, buf + n, BUFFER_SIZE - n, &n);
	line = ft_cut(line, &n);
	return (line);
}
