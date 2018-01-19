/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_getmodes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/11 18:07:48 by mmerabet          #+#    #+#             */
/*   Updated: 2018/01/19 16:38:03 by mmerabet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/xattr.h>
#include <sys/acl.h>

#include "ft_ls.h"
#include "ft_mem.h"

static void	check_type(mode_t st_mode, char *buffer)
{
	if (S_ISLNK(st_mode))
		buffer[0] = 'l';
	else if (S_ISDIR(st_mode))
		buffer[0] = 'd';
	else if (S_ISBLK(st_mode))
		buffer[0] = 'b';
	else if (S_ISCHR(st_mode))
		buffer[0] = 'c';
	else if (S_ISSOCK(st_mode))
		buffer[0] = 's';
	else if (S_ISFIFO(st_mode))
		buffer[0] = 'p';
}

static void	check_owner_rights(mode_t st_mode, char *buffer)
{
	if (st_mode & S_IRUSR)
		buffer[1] = 'r';
	if (st_mode & S_IWUSR)
		buffer[2] = 'w';
	if (st_mode & S_IXUSR)
	{
		if (st_mode & S_ISUID)
			buffer[3] = 's';
		else
			buffer[3] = 'x';
	}
	else if (st_mode & S_ISUID)
		buffer[3] = 'S';
}

static void	check_group_rights(mode_t st_mode, char *buffer)
{
	if (st_mode & S_IRGRP)
		buffer[4] = 'r';
	if (st_mode & S_IWGRP)
		buffer[5] = 'w';
	if (st_mode & S_IXGRP)
	{
		if (st_mode & S_ISGID)
			buffer[6] = 's';
		else
			buffer[6] = 'x';
	}
	else if (st_mode & S_ISGID)
		buffer[6] = 'S';
}

static void	check_other_rights(mode_t st_mode, char *buffer)
{
	if (st_mode & S_IROTH)
		buffer[7] = 'r';
	if (st_mode & S_IWOTH)
		buffer[8] = 'w';
	if (st_mode & S_IXOTH)
	{
		if (st_mode & S_ISVTX)
			buffer[9] = 't';
		else
			buffer[9] = 'x';
	}
	else if (st_mode & S_ISVTX)
		buffer[9] = 'T';
}

void		ls_getmodes(struct stat file_stat, const char *path, char *buffer)
{
	acl_t		acl;

	if (!buffer)
		return ;
	ft_memset((void *)buffer, '-', 10);
	buffer[10] = ' ';
	check_type(file_stat.st_mode, buffer);
	check_owner_rights(file_stat.st_mode, buffer);
	check_group_rights(file_stat.st_mode, buffer);
	check_other_rights(file_stat.st_mode, buffer);
	if (listxattr(path, NULL, 0, XATTR_NOFOLLOW) > 0)
		buffer[10] = '@';
	else if ((acl = acl_get_file(path, ACL_TYPE_EXTENDED)))
	{
		buffer[10] = '+';
		acl_free((void *)acl);
	}
}
