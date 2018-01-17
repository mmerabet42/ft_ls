/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/12 18:57:45 by mmerabet          #+#    #+#             */
/*   Updated: 2018/01/17 19:22:11 by mmerabet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include "libft.h"
#include <fcntl.h>
#include <time.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>

void		listfiles(t_btree *files, const t_lsops *lsops)
{
	t_list	*lst;
	t_file	*file;

	if (!files || !lsops)
		return ;
	lst = (lsops->options & LSF_R ? ft_btree_tolistv(files) :
			ft_btree_tolist(files));
	if (lsops->options & LSF_L)
		ls_printlong(lst, lsops);
	else
		ls_printnormal(lst, lsops);
	if (lsops->options & LSF_R_M)
	{
		while (lst)
		{
			if ((file = (t_file *)lst->content) && file->modes[0] == 'd'
					&& !(ft_strequ(file->name, ".") || ft_strequ(file->name, "..")))
			{
				ft_printf("\n");
				ft_printf("%s:\n", file->full_name);
				files = ls_getfiles(file->full_name, lsops);
				if (!files)
					ft_printf_fd(2, "ft_ls: %s: %s\n", file->name,
							strerror(errno));
				else
					listfiles(files, lsops);
			}
			lst = lst->next;
		}
	}
}

int			main(int argc, char **argv)
{
	t_lsops			*lsops;
	t_list			*lst;
	t_btree			*files;

	if (!(lsops = ls_getoptions(argc, argv)))
		return (0);
	if (lsops->err)
		ft_printf_fd(2, "ft_ls: illegal option -- %c\n"
				"usage: ft_ls [-%s] [file ...]\n", lsops->err, LSFLAGS);
	else
	{
		lst = (lsops->files ? ft_lstsort(lsops->files) : ft_lstcreate(".", 2));
		while (lst)
		{
			files = ls_getfiles((char *)lst->content, lsops);
			if (!files)
				ft_printf_fd(2, "ft_ls: %s: %s\n", lst->content,
						strerror(errno));
			else
			{
				if (lst->next || lst->parent)
					ft_printf("%s:\n", lst->content);
				listfiles(files, lsops);
			}
			if (lst->next)
				ft_putstr("\n");
			lst = lst->next;
		}
		ft_timefdel(&lsops->current);
	}
	ft_lstdel(&lsops->files, NULL);
	free(lsops);
	return (0);
}
