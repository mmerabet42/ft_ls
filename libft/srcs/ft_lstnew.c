/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/11 17:31:55 by mmerabet          #+#    #+#             */
/*   Updated: 2017/12/19 22:41:39 by mmerabet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_list.h"
#include "ft_mem.h"

t_list	*ft_lstnew(const void *content, size_t content_size)
{
	t_list	*lst;

	if ((lst = (t_list *)ft_memalloc(sizeof(t_list))))
	{
		if (content)
		{
			if (!(lst->content = ft_memdup(content, content_size)))
			{
				free(lst);
				return (NULL);
			}
		}
		lst->content_size = (content ? content_size : 0);
	}
	return (lst);
}

t_list	*ft_lstcreate(void *content, size_t content_size)
{
	t_list	*lst;

	if ((lst = (t_list *)ft_memalloc(sizeof(t_list))))
	{
		lst->content = content;
		lst->content_size = (content ? content_size : 0);
	}
	return (lst);
}

void	ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	t_list	*nxt;

	nxt = (alst && *alst ? (*alst)->next : NULL);
	ft_lstdelone(alst, del);
	if (nxt)
		ft_lstdel(&nxt, del);
}

void	ft_lstdelone(t_list **alst, void (*del)(void *, size_t))
{
	if (alst && *alst)
	{
		if (del)
			del((*alst)->content, (*alst)->content_size);
		ft_memdel((void **)alst);
	}
}
