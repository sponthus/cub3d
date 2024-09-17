/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_str.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sponthus <sponthus@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 15:42:37 by sponthus          #+#    #+#             */
/*   Updated: 2024/09/17 15:43:16 by sponthus         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str && str[i])
		i++;
	return (i);
}

size_t	ft_strlcpy(char *dst, char *src, size_t size)
{
	size_t	i;

	if (src && size > 0)
	{
		i = 0;
		while (src[i] != '\0' && i < (size - 1))
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = '\0';
	}
	return (ft_strlen(src));
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (0);
	if (s1 == NULL)
		return (-1);
	else if (s2 == NULL)
		return (1);
	while (s1[i] && s2[i] && s1[i] == s2[i] && i < n - 1)
		i++;
	return ((int )((unsigned char)s1[i] - (unsigned char)s2[i]));
}

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	llen;

	llen = ft_strlen((char *)little);
	if (llen == 0)
		return ((char *)big);
	i = 0;
	while (big[i] && i <= len)
	{
		if (i + llen <= len && ft_strncmp(&big[i], little, llen) == 0)
			return ((char *)&big[i]);
		i++;
	}
	return (NULL);
}


char	*ft_strtrim(char *s1, char *set)
{
	char	*str;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (s1[i] && is_charset(s1[i], (char *)set) == 1)
		i++;
	while (s1[i + j])
		j++;
	j--;
	while (is_charset(s1[i + j], (char *)set) == 1 && j >= 0)
		j--;
	j++;
	str = malloc (sizeof (char) * (j + 1));
	if (!str)
		return (NULL);
	ft_strlcpy(str, s1 + i, j + 1);
	return (str);
}
