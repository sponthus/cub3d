/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sponthus <sponthus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 12:53:09 by sponthus          #+#    #+#             */
/*   Updated: 2024/09/19 14:54:05 by sponthus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*ptr;

	if (!new)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	ptr = *lst;
	while (ptr->next != 0)
		ptr = ptr->next;
	ptr->next = new;
	return ;
}

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	if (new)
	{
		new->next = *lst;
		*lst = new;
	}
	return ;
}

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*ptr;
	t_list	*temp;

	if (lst && del)
	{
		ptr = *lst;
		while (ptr)
		{
			temp = ptr->next;
			(*del)(ptr->content);
			free(ptr);
			ptr = temp;
		}
		*lst = NULL;
	}
	return ;
}

void	ft_lstdelone(t_list *lst, void (*del)(void*))
{
	if (lst && del)
	{
		(*del)(lst->content);
		free(lst);
	}
	return ;
}

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	if (lst && f)
	{
		while (lst)
		{
			(*f)(lst->content);
			lst = lst->next;
		}
	}
	return ;
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


