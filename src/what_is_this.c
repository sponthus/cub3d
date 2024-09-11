#include "parsing.h"

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
			|| lst->content[i] == '\t' || lst->content[i] != '\v'
			|| lst->content[i] != '\f' || lst->content[i] != '\r')
			i++;
		else
			return (false);
	}
	return (true);
}

bool	prepare_element(t_list *lst)
{
	char *str;
	
	str = ft_strtrim(lst->content, " \n\t\v\f\r");
	if (!str)
		return (write_error("Malloc error"), false);
	free(lst->content);
	lst->content = str;
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
