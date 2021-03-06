/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_filenew.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/12 23:02:02 by mmerabet          #+#    #+#             */
/*   Updated: 2018/01/28 21:01:15 by mmerabet         ###   ########.fr       */
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

static char		*getfullpath(const char *path, const char *fname)
{
	char		*final;
	size_t		pathl;
	size_t		fnamel;
	int			l;

	pathl = ft_strlen(path);
	fnamel = ft_strlen(fname);
	l = (path[pathl - 1] == '/' ? 1 : 0);
	if (!(final = ft_strnew(pathl + fnamel + (!l ? 1 : 0))))
		return ((char *)fname);
	ft_strcat(final, path);
	if (!l)
		ft_strcatc(final, '/');
	ft_strcat(final, fname);
	return (final);
}

static t_btree	*ls_readdir(const char *path,
					DIR *dir, int hidden_files, t_cmpfunc sortfunc)
{
	t_btree			*bt;
	t_file			*file;
	struct dirent	*ent;
	char			*fullpath;

	bt = NULL;
	while ((ent = readdir(dir)))
	{
		if (ent->d_name[0] != '.' || (ent->d_name[0] == '.' && hidden_files))
		{
			if ((hidden_files & LSF_A_M) && (ft_strequ(ent->d_name, ".")
						|| ft_strequ(ent->d_name, "..")))
				continue ;
			fullpath = getfullpath(path, ent->d_name);
			if ((file = ls_getfile(fullpath)))
				ft_btree_insertf_p(&bt, ft_btree_create(file, sizeof(t_file)),
						sortfunc);
			free(fullpath);
		}
	}
	return (bt);
}

t_btree			*ls_getfiles(const char *path,
						int hidden_files, t_cmpfunc sortfunc)
{
	t_btree	*bt;
	t_file	*file;
	DIR		*dir;

	if (!(dir = opendir(path)))
	{
		if (errno == ENOTDIR && (file = ls_getfile(path)))
			return (ft_btree_create(file, sizeof(t_file)));
		else
			return (NULL);
	}
	bt = ls_readdir(path, dir, hidden_files, sortfunc);
	closedir(dir);
	return (bt);
}

t_file			*ls_getfile(const char *path)
{
	t_file		*f;
	struct stat	fst;

	if (!path || lstat(path, &fst) == -1
			|| !(f = ft_memalloc(sizeof(t_file))))
		return (NULL);
	f->fst = fst;
	f->name = ft_strrchr(path, '/');
	f->name = ft_strdup(f->name ? f->name + 1 : path);
	f->full_name = ft_strdup(path);
	ft_bzero((void *)f->modes, sizeof(char) * 12);
	ft_bzero((void *)f->link_name, sizeof(char) * 512);
	ls_getmodes(f->fst, path, f->modes);
	f->grp_name = ls_getgrpname(f->fst.st_gid);
	f->usr_name = ls_getusrname(f->fst.st_uid);
	f->mtime = ft_timefnew(&f->fst.st_mtime);
	f->atime = ft_timefnew(&f->fst.st_atime);
#ifdef __linux__
	f->btime = NULL;
#else
	f->btime = ft_timefnew(&f->fst.st_birthtime);
#endif
	f->major = major(f->fst.st_rdev);
	f->minor = minor(f->fst.st_rdev);
	if (f->modes[0] == 'l')
		readlink(path, f->link_name, 512);
	return (f);
}

void			ls_filedel(t_file **file)
{
	free((*file)->name);
	free((*file)->full_name);
	free((*file)->usr_name);
	free((*file)->grp_name);
	ft_timefdel(&(*file)->mtime);
	ft_timefdel(&(*file)->atime);
	ft_timefdel(&(*file)->btime);
	ft_memdel((void **)file);
}
