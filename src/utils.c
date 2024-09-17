/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sponthus <sponthus@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 17:01:20 by sponthus          #+#    #+#             */
/*   Updated: 2024/09/17 13:16:25 by sponthus         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*ptr;

	ptr = (unsigned char *)s;
	while (n > 0)
	{
		*ptr = 0;
		ptr++;
		n--;
	}
	return ;
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*ptr;

	if (nmemb * size != 0 && (nmemb * size) / nmemb != size)
		return (NULL);
	ptr = malloc (nmemb * size);
	if (!ptr)
		return (NULL);
	ft_bzero(ptr, nmemb * size);
	return (ptr);
}

char	*ft_strdup(char *s)
{
	char	*res;
	size_t	len;

	len = ft_strlen(s);
	res = ft_calloc(len + 1, sizeof (char ));
	if (!res)
		return (NULL);
	ft_strlcpy(res, s, len + 1);
	return (res);
}


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

int	is_charset(char c, char	*charset)
{
	int	i;

	i = 0;
	while (charset[i])
	{
		if (c == charset[i])
			return (1);
		i++;
	}
	return (0);
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
