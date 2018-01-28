/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/12 18:57:45 by mmerabet          #+#    #+#             */
/*   Updated: 2018/01/28 22:39:15 by mmerabet         ###   ########.fr       */
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

	errno = 0;
	file = (t_file *)bt->content;
	if ((bt->parent || bt->left || bt->right
				|| (lsops->files && lsops->folders) || lsops->n_err)
			&& file->modes[0] == 'd')
		ft_printf("%s:\n", file->full_name);
	islast = (bt == lsops->last);
	if (!(files = ls_getfiles(file->full_name,
					lsops->options & (LSF_A | LSF_A_M), lsops->sortfunc))
			&& errno != 0)
		ft_printf_fd(2, "ls: %s: %s\n", file->name, strerror(errno));
	else
		ls_listfiles(files, lsops);
	if (!islast)
		ft_printf("\n");
}

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

static void	presetls(t_lsops *lsops, char **envp)
{
	if (lsops->options & LSF_G_M)
		set_lscolors(envp);
	if (lsops->options & LSF_N)
	{
		lsops->options |= LSF_L;
		ls_keepid();
	}
	if (lsops->options & LSF_F)
	{
		lsops->options |= LSF_A;
		lsops->options ^= LSF_A_M;
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
		presetls(lsops, envp);
		ls_listfiles(lsops->files, lsops);
		if (lsops->folders && lsops->files)
			ft_printf("\n");
		if (lsops->options & LSF_R)
			ft_btree_iterv_d(lsops->folders, (void(*)(t_btree *, void *))ft_ls,
					(void *)lsops);
		else
			ft_btree_iter_d(lsops->folders, (void(*)(t_btree *, void *))ft_ls,
					(void *)lsops);
	}
	ls_lsopsdel(&lsops);
	ft_printf_free_formats();
	return (0);
}
