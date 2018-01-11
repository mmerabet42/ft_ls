/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_getnames.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/11 22:49:41 by mmerabet          #+#    #+#             */
/*   Updated: 2018/01/11 23:04:57 by mmerabet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include <grp.h>
#include <pwd.h>

void	ls_getnames(struct stat file_stat, char **grp_name, char **usr_name)
{
	struct group	*grp;
	struct passwd	*usr;

	if (!grp_name || !usr_name)
		return ;
	*grp_name = NULL;
	*usr_name = NULL;
	if ((grp = getgrgid(file_stat.st_gid)))
		*grp_name = grp->gr_name;
	if ((usr = getpwuid(file_stat.st_uid)))
		*usr_name = usr->pw_name;
}
