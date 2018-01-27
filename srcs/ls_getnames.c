/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_getnames.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/11 22:49:41 by mmerabet          #+#    #+#             */
/*   Updated: 2018/01/27 21:24:12 by mmerabet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include "ft_mem.h"
#include "ft_str.h"
#include "ft_types.h"
#include <grp.h>
#include <pwd.h>

static int	g_keepid;

void	ls_keepid(void)
{
	g_keepid = 1;
}

char	*ls_getgrpname(gid_t gid)
{
	struct group	*grp;
	char			*nm;

	nm = NULL;
	if (!g_keepid && (grp = getgrgid(gid)))
		nm = ft_strdup(grp->gr_name);
	else
		nm = ft_uitoa(gid);
	return (nm);
}

char	*ls_getusrname(uid_t uid)
{
	struct passwd	*usr;
	char			*nm;

	nm = NULL;
	if (!g_keepid && (usr = getpwuid(uid)))
		nm = ft_strdup(usr->pw_name);
	else
		nm = ft_uitoa(uid);
	return (nm);
}

void	ls_filedel_func(void *content, size_t n)
{
	t_file	*f;

	(void)n;
	f = (t_file *)content;
	ls_filedel(&f);
}

void	ls_lsopsdel(t_lsops **lsops)
{
	ft_btree_del(&(*lsops)->files, ls_filedel_func);
	ft_timefdel(&(*lsops)->current);
	ft_memdel((void **)lsops);
}
