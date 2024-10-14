/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_01.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: endoliam <endoliam@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 15:14:41 by endoliam          #+#    #+#             */
/*   Updated: 2024/10/14 15:15:38 by endoliam         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*newlst;
	t_list	*tmplst;
	void	*c;

	newlst = NULL;
	while (lst && (*f) && (*del))
	{
		c = (*f)(lst->content);
		if (!c)
		{
			ft_lstclear(&newlst, del);
			return (NULL);
		}
		tmplst = ft_lstnew(c);
		if (!tmplst)
		{
			(*del)(c);
			ft_lstclear(&newlst, del);
			return (NULL);
		}
		ft_lstadd_back(&newlst, tmplst);
		lst = lst->next;
	}
	return (newlst);
}

t_list	*ft_lstnew(void *content)
{
	t_list	*new;

	new = malloc (sizeof (t_list) * 1);
	if (!new)
		return (NULL);
	new->content = content;
	new->next = NULL;
	new->size = ft_strlen(content);
	new->empty = true;
	new->map = false;
	new->id = NULL;
	return (new);
}

int	ft_lstsize(t_list *lst)
{
	int	count;

	if (!lst)
		return (0);
	count = 1;
	while (lst->next)
	{
		lst = lst->next;
		count++;
	}
	return (count);
}

t_list	*ft_lstlast(t_list *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
	{
		lst = lst->next;
	}
	return (lst);
}
