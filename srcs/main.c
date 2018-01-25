/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/12 18:57:45 by mmerabet          #+#    #+#             */
/*   Updated: 2018/01/25 23:42:52 by mmerabet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include "ft_printf_ext.h"
#include "ft_printf.h"
#include "ft_str.h"
#include <fcntl.h>
#include <time.h>
#include <string.h>
#include <errno.h>

static void	ft_ls(t_btree *bt, const t_lsops *lsops)
{
	t_btree	*files;
	t_file	*file;
	int		islast;

	file = (t_file *)bt->content;
	islast = (bt == lsops->last);
	if (!(files = ls_getfiles(file->full_name,
					lsops->options & (LSF_A | LSF_A_M), lsops->sortfunc))
			&& errno != 0)
		ft_printf_fd(2, "ft_ls: %s: %s\n", file->full_name,
				strerror(errno));
	else if (files)
	{
		if (bt->parent || bt->left || bt->right)
			ft_printf("%s:\n", file->full_name);
		ls_listfiles(files, lsops);
	}
	if (!islast)
		ft_printf("\n");
}
/*
static void	ft_ls(const t_lsops *lsops)
{
	t_list	*lst;
	t_btree	*files;

	lst = lsops->files;
	while (lst)
	{
		if (!(files = ls_getfiles((char *)lst->content,
						lsops->options & (LSF_A | LSF_A_M), lsops->sortfunc))
				&& errno != 0)
			ft_printf_fd(2, "ft_ls: %s: %s\n", lst->content,
					strerror(errno));
		else if (files)
		{
			if (lst->next || lst->parent)
				ft_printf("%s:\n", lst->content);
			ls_listfiles(files, lsops);
		}
		if ((lst = lst->next))
			ft_printf("\n");
	}
}

** 0;255;145
** 85;226;165
*/

static void	set_lscolors(char **envp)
{
	while (*envp)
	{
		if (ft_strmatch(*envp, "LSCOLORS=*"))
		{
			ls_setlocale_color(ft_strchr(*envp, '=') + 1);
			break ;
		}
		++envp;
	}
}

int			main(int argc, char **argv, char **envp)
{
	t_lsops			*lsops;

	if (!(lsops = ls_getlsops(argc, argv)))
		return (0);
	if (lsops->err)
		ft_printf_fd(2, "ft_ls: illegal option -- %c\n"
				"usage: ft_ls [-%s] [file ...]\n", lsops->err, LSFLAGS);
	else
	{
		if (lsops->options & LSF_G)
			set_lscolors(envp);
		if (lsops->options & LSF_R)
			ft_btree_iterv_d(lsops->files, (void(*)(t_btree *, void *))ft_ls,
					(void *)lsops);
		else
			ft_btree_iter_d(lsops->files, (void(*)(t_btree *, void *))ft_ls,
					(void *)lsops);
		//ft_ls(lsops);
	}
	ls_lsopsdel(&lsops);
	ft_printf_free_formats();
	return (0);
}
