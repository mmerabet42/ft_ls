/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/12 18:57:45 by mmerabet          #+#    #+#             */
/*   Updated: 2018/01/19 22:39:39 by mmerabet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include "libft.h"
#include <fcntl.h>
#include <time.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>

static t_cmpfunc	getcmpfunc(t_lsops *lsops)
{
	if (lsops->options & LSF_T)
		return (ls_cmpfile_time);
	return (ls_cmpfile_name);
}

static void			filesdel(void *content, size_t n)
{
	t_file	*file;

	(void)n;
	file = (t_file *)content;
	ls_filedel(&file);
}

static void			listfiles(t_btree *files, const t_lsops *lsops,
						t_cmpfunc sortfunc)
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
				ft_printf("\n%s:\n", file->full_name);
				if (!(files = ls_getfiles(file->full_name,
							lsops->options & LSF_A, sortfunc)) && errno != 0)
					ft_printf_fd(2, "ft_ls: %s: %lu %s\n", file->name,
							errno, strerror(errno));
				else if (files)
					listfiles(files, lsops, sortfunc);
				ft_btree_del(&files, NULL);
			}
			lst = lst->next;
		}
	}
	ft_lstdel(&lst, filesdel);
}

void btiter(t_btree *bt, void *data)
{
	ft_printf("DATA %d : %s\n", (*(int *)data)++, bt->content);
}

int			main(int argc, char **argv)
{
	t_btree	*bt = NULL, *tmp;
	int	i = 1;
	while (i < argc)
	{
		tmp = ft_btree_insert(bt, ft_btree_create(argv[i], ft_strlen(argv[i]) + 1));
		if (!bt)
			bt = tmp;
		++i;
	}
	int data = 0;
	ft_btree_iter_d(bt, btiterm &data);
	return (0);
	t_lsops			*lsops;
	t_list			*lst;
	t_btree			*files;
	t_cmpfunc		sortfunc;

	if (!(lsops = ls_getoptions(argc, argv)))
		return (0);
	lst = NULL;
	if (lsops->err)
		ft_printf_fd(2, "ft_ls: illegal option -- %c\n"
				"usage: ft_ls [-%s] [file ...]\n", lsops->err, LSFLAGS);
	else
	{
		sortfunc = getcmpfunc(lsops);
		lst = (lsops->files ? ft_lstsort(lsops->files) : ft_lstcreate(".", 2));
		while (lst)
		{
			if (!(files = ls_getfiles((char *)lst->content,
							lsops->options & LSF_A, sortfunc)) && errno != 0)
				ft_printf_fd(2, "ft_ls: %s: %lu %s\n", lst->content,
						errno, strerror(errno));
			else if (files)
			{
				if (lst->next || lst->parent)
					ft_printf("%s:\n", lst->content);
				listfiles(files, lsops, sortfunc);
			}
			if ((lst = lst->next))
				ft_putstr("\n");
			ft_btree_del(&files, NULL);
		}
		ft_timefdel(&lsops->current);
	}
	ft_lstdel(&lst, NULL);
	free(lsops);
	return (0);
}
