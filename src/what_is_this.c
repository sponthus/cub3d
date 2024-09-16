/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   what_is_this.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sponthus <sponthus@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 12:53:17 by sponthus          #+#    #+#             */
/*   Updated: 2024/09/16 14:28:53 by sponthus         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	determine_content(t_list *lst)
{
	int	i;

	i = ft_strlen(lst->id);
	while (lst->content[i] && (lst->content[i] == ' ' || lst->content[i] == '\n'
			|| lst->content[i] == '\t' || lst->content[i] == '\v'
			|| lst->content[i] == '\f' || lst->content[i] == '\r'))
		i++;
	if (i != lst->size)
		ft_strlcpy(&lst->content[0], &lst->content[i], lst->size);
	else
	{
		write_error("Content is empty : ", lst->id);
		return (1);
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
	char *str;
	
	str = ft_strtrim(lst->content, " \n\t\v\f\r");
	if (!str)
	{
		write_error("Malloc error", NULL);
		return (false);
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
					write_error("Unexpected element after map : ", actual->content);
					return (false);
				}
				actual->map = true;
				actual = actual->next;
			}
		}
	}
	return (true);
}
