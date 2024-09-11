/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: endoliam <endoliam@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 17:01:20 by sponthus          #+#    #+#             */
/*   Updated: 2024/09/10 23:29:15 by endoliam         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
		i++;
	return (i);
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

char	*ft_strtrim(char const *s1, char const *set)
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
