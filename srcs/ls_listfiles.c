/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_listfiles.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/25 20:34:52 by mmerabet          #+#    #+#             */
/*   Updated: 2018/01/28 21:05:13 by mmerabet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include <errno.h>
#include <string.h>
#include "ft_printf.h"
#include "ft_str.h"

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

	errno = 0;
	if ((file = (t_file *)bt->content) && file->modes[0] == 'd'
			&& !(ft_strequ(file->name, ".") || ft_strequ(file->name, "..")))
	{
		ft_printf("\n%s:\n", file->full_name);
		if (!(files = ls_getfiles(file->full_name, lsops->options & LSF_A,
						lsops->sortfunc)) && errno != 0)
			ft_printf_fd(2, "ls: %s: %s\n", file->name,
					strerror(errno));
		else if (files)
			ls_listfiles(files, lsops);
	}
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
	if (files != lsops->files)
		ft_btree_del(&files, filesdel);
}
