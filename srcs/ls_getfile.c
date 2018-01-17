/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_filenew.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/12 23:02:02 by mmerabet          #+#    #+#             */
/*   Updated: 2018/01/17 19:21:58 by mmerabet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include "ft_mem.h"
#include "ft_printf.h"
#include "ft_str.h"
#include <fcntl.h>
#include <dirent.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>

t_btree		*ls_getfiles(const char *file_name,
						const t_lsops *lsops)
{
	t_btree			*bt;
	t_btree			*tmp;
	t_file			*file;
	DIR				*d;
	struct dirent	*ent;
	char			*final;

	if (!(d = opendir(file_name)))
	{
		if (errno == ENOTDIR && (file = ls_getfile(file_name, lsops->current)))
			return (ft_btree_create(file, sizeof(t_file)));
		else
			return (NULL);
	}
	bt = NULL;
	while ((ent = readdir(d)))
	{
		if (ent->d_name[0] != '.' ||
				(ent->d_name[0] == '.' && lsops->options & LSF_A))
		{
			ft_printf_s(&final, "%s%s%s", file_name, (file_name[ft_strlen(file_name) - 1] == '/' ? "" : "/"), ent->d_name);
			if ((file = ls_getfile(final, lsops->current)))
			{
				tmp = ft_btree_insertf(bt, ft_btree_create(file,
							sizeof(t_file)), lsops->sortfunc);
				if (!bt)
					bt = tmp;
			}
			free(final);
		}
	}
	closedir(d);
	return (bt);
}

t_file		*ls_getfile(const char *file_name)
{
	t_file		*f;
	struct stat	fst;

	if (!file_name || lstat(file_name, &fst) == -1
			|| !(f = ft_memalloc(sizeof(t_file))))
		return (NULL);
	f->fst = fst;
	if ((f->name = ft_strrchr(file_name, '/')))
		f->name = ft_strdup(f->name + 1);
	else
		f->name = ft_strdup(file_name);
	f->full_name = ft_strdup(file_name);
	ft_bzero((void *)f->modes, sizeof(char) * 12);
	ft_bzero((void *)f->link_name, sizeof(char) * 512);
	ls_getmodes(f->fst, file_name, f->modes);
	f->grp_name = ls_getgrpname(f->fst.st_gid);
	f->usr_name = ls_getusrname(f->fst.st_uid);
	f->mtime = ft_timefnew(&f->fst.st_mtime);
	f->major = major(f->fst.st_rdev);
	f->minor = minor(f->fst.st_rdev);
	if (f->modes[0] == 'l')
		readlink(file_name, f->link_name, 512);
	return (f);
}
