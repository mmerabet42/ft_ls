/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_getnames.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/11 22:49:41 by mmerabet          #+#    #+#             */
/*   Updated: 2018/01/12 23:01:15 by mmerabet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
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

int		ls_isfar(t_timef *a, t_timef *b)
{
	if (!a || !b)
		return (0);
	if ((int)a->month < (int)b->month - 6 || (int)a->month > (int)b->month + 6)
		return (1);
	return (0);
}
