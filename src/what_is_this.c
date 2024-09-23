/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   what_is_this.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sponthus <sponthus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 12:53:17 by sponthus          #+#    #+#             */
/*   Updated: 2024/09/23 12:15:04 by sponthus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	resize_content(t_list *lst)
{
	int	i;

	i = ft_strlen(lst->id);
	while (lst->content[i] && (lst->content[i] == ' ' || lst->content[i] == '\n'
			|| lst->content[i] == '\t' || lst->content[i] == '\v'
			|| lst->content[i] == '\f' || lst->content[i] == '\r'))
		i++;
	if (i != lst->size)
	{
		ft_strlcpy(&lst->content[0], &lst->content[i], lst->size);
		lst->size = ft_strlen(lst->content);
	}
	else
	{
		return (write_error("Content is empty", lst->id, NULL, 1));
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
		if (lst->content[i] == ' ' || lst->content[i] == '\n'
			|| lst->content[i] == '\t' || lst->content[i] == '\v'
			|| lst->content[i] == '\f' || lst->content[i] == '\r')
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

	str = ft_strtrim(lst->content, " \n\t\v\f\r");
	if (!str)
	{
		return (write_error(ERR_MALLOC, NULL, NULL, false));
	}
	free(lst->content);
	lst->content = str;
	lst->size = ft_strlen(str);
	return (true);
}

bool	is_element(t_list *lst, char *id)
{
	int	len;

	len = ft_strlen(id);
	if (ft_strncmp(lst->content, id, len) == 0) // J'ai mon ID complet
	{
		if (lst->size > len + 1
			&& is_charset(lst->content[len], " \n\t\v\f\r")) // Suivi d'un espace
		{
			lst->id = id;
			return (true);
		}
	}
	else if (len == 2 && ft_strncmp(lst->content, id, 1) == 0) // J'ai la 1e lettre de l'ID
	{
		if (lst->size > 2
			&& is_charset(lst->content[1], " \n\t\v\f\r")) // Suivie d'un espace
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
	return (write_error("Found an expected element", actual->content, NULL, false));
}
