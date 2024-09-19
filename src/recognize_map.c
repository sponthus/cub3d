/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recognize_map.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sponthus <sponthus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 11:25:34 by sponthus          #+#    #+#             */
/*   Updated: 2024/09/19 14:54:03 by sponthus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	list_map_size(t_list *lst)
{
	int	i;

	i = 0;
	while (lst)
	{
		i++;
		lst = lst->next;
	}
	return (i);
}

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
	t_list	*actual;

	actual = lst;
	if (is_map_element(lst) == true)
	{
		if (lst->map == false)
		{
			while (actual)
			{
				if (is_map_element(actual) == false)
				{
					return (write_error("Unexpected element after map", actual->content, false));
				}
				actual->map = true;
				actual = actual->next;
			}
		}
	}
	return (true);
}
