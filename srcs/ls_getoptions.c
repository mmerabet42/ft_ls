/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_getoptions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/11 18:07:29 by mmerabet          #+#    #+#             */
/*   Updated: 2018/01/28 22:26:06 by mmerabet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include "ft_str.h"
#include "ft_mem.h"
#include "ft_list.h"
#include "ft_math.h"
#include "ft_printf.h"
#include <string.h>
#include <errno.h>

static t_cmpfunc	getcmpfunc(t_lsops *lsops)
{
	if (lsops->options & LSF_F)
		return (ls_cmpfile_no);
	else if (lsops->options & LSF_S_M)
		return (ls_cmpfile_size);
	else if (lsops->options & LSF_T)
	{
		if (lsops->options & LSF_U_M)
			return (ls_cmpfile_btime);
		else if (lsops->options & LSF_U)
			return (ls_cmpfile_atime);
		return (ls_cmpfile_mtime);
	}
	return (ls_cmpfile_name);
}

static int			get_flag(char c)
{
	static int	lsfs_size = sizeof(LSFLAGS);
	int			i;

	i = -1;
	while (++i < lsfs_size)
		if (LSFLAGS[i] == c)
			return (1 << i);
	return (0);
}

static int			get_flags(int argc, char **argv, t_lsops *lsops)
{
	int	i;
	int	j;
	int	flag;

	i = 0;
	while (++i < argc)
	{
		if (argv[i][0] == '-')
		{
			j = 0;
			while (argv[i][++j])
			{
				if (!(flag = get_flag(argv[i][j])))
					return ((int)(lsops->err = argv[i][j]));
				lsops->options |= flag;
			}
		}
		else
			break ;
	}
	return (i);
}

static void			get_files(int argc, char **argv, int istart,
							t_lsops *lsops)
{
	t_file	*file;

	while (istart < argc)
	{
		if ((file = ls_getfile(argv[istart])))
		{
			if (file->modes[0] != 'd')
			{
				free(file->name);
				file->name = ft_strdup(file->full_name);
				ft_btree_insertf_p(&lsops->files,
						ft_btree_create(file, sizeof(t_file)), lsops->sortfunc);
			}
			else
				ft_btree_insertf_p(&lsops->folders,
						ft_btree_create(file, sizeof(t_file)), lsops->sortfunc);
		}
		else
		{
			ft_printf_fd(2, "ft_ls: %s: %s\n", argv[istart], strerror(errno));
			lsops->n_err = 1;
		}
		++istart;
	}
}

t_lsops				*ls_getlsops(int argc, char **argv)
{
	t_lsops	*lsops;
	t_file	*file;
	int		i;

	if (!(lsops = (t_lsops *)ft_memalloc(sizeof(t_lsops))))
		return (NULL);
	lsops->current = ft_timefnew(NULL);
	i = get_flags(argc, argv, lsops);
	lsops->sortfunc = getcmpfunc(lsops);
	if (!lsops->err)
	{
		get_files(argc, argv, i, lsops);
		if (!lsops->files && !lsops->folders && !errno
				&& (file = ls_getfile(".")))
			lsops->folders = ft_btree_create(file, sizeof(t_file));
		lsops->last = (lsops->options & LSF_R ? ft_btree_left(lsops->folders)
				: ft_btree_right(lsops->folders));
	}
	return (lsops);
}
