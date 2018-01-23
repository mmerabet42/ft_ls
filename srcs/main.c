/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/12 18:57:45 by mmerabet          #+#    #+#             */
/*   Updated: 2018/01/23 22:33:31 by mmerabet         ###   ########.fr       */
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

static void	filesdel(void *content, size_t n)
{
	t_file	*file;

	(void)n;
	file = (t_file *)content;
	ls_filedel(&file);
}

static void	rlistfiles(t_btree *bt, const t_lsops *lsops)
{
	t_file	*file;
	t_btree	*files;

	if ((file = (t_file *)bt->content) && file->modes[0] == 'd'
			&& !(ft_strequ(file->name, ".") || ft_strequ(file->name, "..")))
	{
		ft_printf("\n%s:\n", file->full_name);
		if (!(files = ls_getfiles(file->full_name,
						lsops->options & LSF_A, lsops->sortfunc)) && errno != 0)
			ft_printf_fd(2, "ft_ls: %s: %s\n", file->name,
					strerror(errno));
		else if (files)
			ls_listfiles(files, lsops);
	}
	errno = 0;
}

void		ls_listfiles(t_btree *files, const t_lsops *lsops)
{
	if (!files || !lsops)
		return ;
	if (lsops->options & LSF_L)
		ls_printlong(files, lsops);
	else
		ls_printnormal(files, lsops);
	if (lsops->options & LSF_R_M)
	{
		if (lsops->options & LSF_R)
			ft_btree_iterv_d(files, (void(*)(t_btree *, void *))rlistfiles,
					(void *)lsops);
		else
			ft_btree_iter_d(files, (void(*)(t_btree *, void *))rlistfiles,
					(void *)lsops);
	}
	ft_btree_del(&files, filesdel);
}

static void	ft_ls(const t_lsops *lsops)
{
	t_list	*lst;
	t_btree	*files;

	lst = lsops->files;
	while (lst)
	{
		if (!(files = ls_getfiles((char *)lst->content,
						lsops->options & LSF_A, lsops->sortfunc)) && errno != 0)
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

/*
** 0;255;145
** 85;226;165
*/

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
		ft_ls(lsops);
	}
	ls_lsopsdel(&lsops);
	ft_printf_free_formats();
	return (0);
}
