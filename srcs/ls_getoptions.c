/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_getoptions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/11 18:07:29 by mmerabet          #+#    #+#             */
/*   Updated: 2018/01/21 17:49:35 by mmerabet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include "ft_str.h"
#include "ft_mem.h"
#include "ft_list.h"
#include "ft_math.h"

static t_cmpfunc	getcmpfunc(t_lsops *lsops)
{
	if (lsops->options & LSF_T)
		return (ls_cmpfile_time);
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
	t_list	*tmp;

	while (istart < argc)
	{
		tmp = ft_lstpush(lsops->files,
				ft_lstcreate(argv[istart], ft_strlen(argv[istart]) + 1));
		if (!lsops->files)
			lsops->files = tmp;
		++istart;
	}
	if (!lsops->files)
		lsops->files = ft_lstcreate(".", 2);
	else
		lsops->files = ft_lstsort(lsops->files);
}

t_lsops				*ls_getlsops(int argc, char **argv)
{
	t_lsops	*lsops;
	int		i;

	if (!(lsops = (t_lsops *)ft_memalloc(sizeof(t_lsops))))
		return (NULL);
	lsops->current = ft_timefnew(NULL);
	i = get_flags(argc, argv, lsops);
	lsops->sortfunc = getcmpfunc(lsops);
	if (!lsops->err)
		get_files(argc, argv, i, lsops);
	return (lsops);
}
