/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   what_is_this_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sponthus <sponthus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 12:53:17 by sponthus          #+#    #+#             */
/*   Updated: 2024/10/31 15:44:07 by sponthus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing_bonus.h"
#include "errors_bonus.h"

int	resize_content(t_list *lst)
{
	int	i;

	i = ft_strlen(lst->id);
	while (lst->content[i] && is_charset(lst->content[i], WHITESPACES))
		i++;
	if (i != lst->size)
	{
		ft_strlcpy(&lst->content[0], &lst->content[i], lst->size);
		lst->size = ft_strlen(lst->content);
	}
	else
	{
		return (write_err("Content is empty", lst->id, NULL, 1));
	}
	return (0);
}

bool	is_empty(t_list *lst)
{
	int	i;

	i = 0;
	if (lst == NULL)
		return (true);
	if (lst->size == 1)
		return (true);
	while (lst->content[i])
	{
		if (is_charset(lst->content[i], WHITESPACES))
			i++;
		else
		{
			lst->empty = false;
			return (false);
		}
	}
	return (true);
}

bool	prepare_element(t_list *lst)
{
	char	*str;

	str = ft_strtrim(lst->content, WHITESPACES);
	if (!str)
	{
		return (write_err(ERR_MALLOC, NULL, NULL, false));
	}
	free(lst->content);
	lst->content = str;
	lst->size = ft_strlen(str);
	return (true);
}

// Is complete ID present, then spaces
// Or is only first letter present, then spaces
bool	is_element(t_list *lst, char *id)
{
	int	len;

	len = ft_strlen(id);
	if (ft_strncmp(lst->content, id, len) == 0)
	{
		if (lst->size > len + 1
			&& is_charset(lst->content[len], WHITESPACES))
		{
			lst->id = id;
			return (true);
		}
	}
	else if (len == 2 && ft_strncmp(lst->content, id, 1) == 0)
	{
		if (lst->size > 2
			&& is_charset(lst->content[1], WHITESPACES))
		{
			lst->id = id;
			return (true);
		}
	}
	return (false);
}

bool	what_is_it(t_list *actual)
{
	if (is_empty(actual))
		return (true);
	if (handle_map_elements(actual) == false)
		return (false);
	if (actual->map == true)
		return (true);
	if (prepare_element(actual) == false)
		return (false);
	if (is_element(actual, "NO") == true)
		return (true);
	else if (is_element(actual, "SO") == true)
		return (true);
	else if (is_element(actual, "WE") == true)
		return (true);
	else if (is_element(actual, "EA") == true)
		return (true);
	else if (is_element(actual, "F") == true)
		return (true);
	else if (is_element(actual, "C") == true)
		return (true);
	return (write_err(ERR_UNEX, actual->content, NULL, false));
}
