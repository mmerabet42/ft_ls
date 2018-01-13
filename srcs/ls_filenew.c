/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_filenew.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/12 23:02:02 by mmerabet          #+#    #+#             */
/*   Updated: 2018/01/13 23:17:51 by mmerabet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include "ft_mem.h"
#include <fcntl.h>
#include <dirent.h>

static int	ls_isfar(t_timef *a, t_timef *b)
{
	if (!a || !b)
		return (0);
	if ((int)a->month < (int)b->month - 6 || (int)a->month > (int)b->month + 6)
		return (1);
	return (0);
}

static void	ls_getchilds(const t_file *parent, int childs,
				t_cmpfunc sortfunc)
{
	t_btree			*tmp;
	t_file			*file;
	DIR				*d;
	struct dirent	*ent;

	if (!(d = opendir(parent->name)))
		return (NULL);
	while ((ent = readdir(d)))
	{
		if ((file = ls_filenew(ent->d_name, childs, lsops)))
			tmp = ft_btree_insertf(parent->childs, file, sizeof(t_file),
					sortfunc);
		if (!parent->childs)
			parent->childs = tmp;
	}
}

t_file		*ls_filenew(const char *file_name, int childs,
					t_cmpfunc sortfunc)
{
	t_file		*f;
	struct stat	fst;

	if (!file_name || lstat(file_name, &fst) == -1
			|| !(f = ft_memalloc(sizeof(t_file))))
		return (NULL);
	if (!sortfunc)
		sortfunc = ls_cmpfile_name;
	f->file_stat = fst;
	f->name = file_name;
	f->modes = ft_memalloc(sizeof(char) * 12);
	ls_getmodes(f->file_stat, f->modes);
	f->grp_name = ls_getgrpname(f->file_stat.st_gid);
	f->usr_name = ls_getusrname(f->file_stat.st_uid);
	f->mtime = ft_timefnew(&f->file_stat.st_mtime);
	f->isfar = ls_isfar(f->mtime, lsops->current);
	if (childs || S_ISDIR(f->file_stat.st_mode))
		ls_getchilds(f, childs, sortfunc);
	return (f);
}
