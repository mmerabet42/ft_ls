/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_getnames.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/11 22:49:41 by mmerabet          #+#    #+#             */
/*   Updated: 2018/01/21 17:36:08 by mmerabet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include "ft_mem.h"
#include <grp.h>
#include <pwd.h>

char	*ls_getgrpname(gid_t gid)
{
	struct group	*grp;
	char			*nm;

	nm = NULL;
	if ((grp = getgrgid(gid)))
		nm = grp->gr_name;
	return (nm);
}

char	*ls_getusrname(uid_t uid)
{
	struct passwd	*usr;
	char			*nm;

	nm = NULL;
	if ((usr = getpwuid(uid)))
		nm = usr->pw_name;
	return (nm);
}

void	ls_lsopsdel(t_lsops **lsops)
{
	ft_lstdel(&(*lsops)->files, NULL);
	ft_timefdel(&(*lsops)->current);
	ft_memdel((void **)lsops);
}
