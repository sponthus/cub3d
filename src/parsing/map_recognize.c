/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_recognize.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: endoliam <endoliam@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 11:25:34 by sponthus          #+#    #+#             */
/*   Updated: 2024/10/14 14:49:17 by endoliam         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

bool	is_map_element(t_list *lst)
{
	int		i;

	i = 0;
	while (lst->content[i])
	{
		if (is_charset(lst->content[i], " \n\t\v\f\r01NSEW"))
			i++;
		else
		{
			break ;
		}
	}
	if (i == lst->size)
		return (true);
	return (false);
}

void	replace_whitespaces(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (is_charset(str[i], "\n\t\v\f\r"))
			str[i] = ' ';
		i++;
	}
}

bool	empty_mapline(char *str)
{
	int	i;

	i = 0;
	if (str == NULL)
		return (true);
	if (ft_strlen(str) < 2)
		return (true);
	while (str[i])
	{
		if (str[i] == ' ')
			i++;
		else
			return (false);
	}
	return (true);
}

bool	handle_map_elements(t_list *lst)
{
	t_list	*a;

	a = lst;
	if (is_map_element(lst) == true)
	{
		if (lst->map == false)
		{
			while (a)
			{
				if (is_map_element(a) == false)
				{
					return (write_err(ERR_UNEX, a->content,
							"after map", false));
				}
				a->map = true;
				a = a->next;
			}
		}
	}
	return (true);
}
