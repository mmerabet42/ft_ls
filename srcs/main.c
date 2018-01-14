/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/12 18:57:45 by mmerabet          #+#    #+#             */
/*   Updated: 2018/01/14 23:23:36 by mmerabet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include "libft.h"
#include <fcntl.h>
#include <time.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>

t_cmpfunc	getcmpfunc(const t_lsops *lsops)
{
	if (lsops->options & LSF_T)
		return (ls_cmpfile_time);
	return (ls_cmpfile_name);
}

char		*file_fg(t_file *file)
{
	if (file->modes[0] == 'd')
		return ("lblue");
	else if (file->modes[0] == 'l')
		return ("lyellow");
	else if (file->name[0] == '.')
		return ("lgreen");
	return ("white");
}

char		*file_bg(t_file *file)
{
	(void)file;
	return ("");
}

void		getmaxwidth(int maxs[5], t_list *lst)
{
	t_list	*it;
	t_file	*file;

	ft_bzero(maxs, sizeof(int) * 5);
	it = lst;
	while (it)
	{
		if ((file = (t_file *)it->content))
		{
			maxs[0] = ft_max(maxs[0], ft_uintlen(file->file_stat.st_nlink));
			maxs[1] = ft_max(maxs[1], ft_strlen(file->usr_name));
			maxs[2] = ft_max(maxs[2], ft_strlen(file->grp_name));
			maxs[3] = ft_max(maxs[3], ft_uintlen(file->file_stat.st_size));
			maxs[4] = ft_max(maxs[4], ft_strlen(file->name));
		}
		it = it->next;
	}
}

void		listfiles(t_btree *files, const t_lsops *lsops)
{
	t_list	*lst;
	t_file	*file;
	int		maxs[5];

	if (!files || !lsops)
		return ;
	lst = ft_btree_tolist(files);
	getmaxwidth(maxs, lst);
	while (lst)
	{
		if ((file = (t_file *)lst->content))
		{
			if (lsops->options & LSF_L)
			{
				ft_printf("%s %*lu %{lred}%-*s  %-*s%{0}  %*lu "
						"%{cyan}%s %2u %02u:%02u%{0} %{%s}%#{%s}%s%{0}",
						file->modes, maxs[0], file->file_stat.st_nlink,
						maxs[1], file->usr_name, maxs[2], file->grp_name,
						maxs[3], file->file_stat.st_size,
						file->mtime->cmonth, file->mtime->day,
						file->mtime->hour, file->mtime->min,
						file_fg(file), file_bg(file), file->name);
				if (file->link_name[0])
					ft_printf(" -> %s", file->link_name);
				ft_printf("\n");
			}
			else
				ft_printf("%{%s}%#{%s}%-*s%{0}%s", file_fg(file), file_bg(file),
						(lst->next ? maxs[4] : -1), file->name, (lst->next ? " " : ""));
		}
		ft_printf("\n");
		lst = lst->next;
	}
}

int			main(int argc, char **argv)
{
	t_lsops			*lsops;
	t_list			*lst;
	t_btree			*files;
	time_t			cur_t;
	int				file_size;

	if (!(lsops = ls_getoptions(argc, argv)))
		return (0);
	if (lsops->err)
		ft_printf_fd(2, "ft_ls: illegal option -- %c\n"
				"usage: ls [-%s] [file ...]\n", lsops->err, LSFLAGS);
	else
	{
		cur_t = time(NULL);
		lsops->current = ft_timefnew(&cur_t);
		lst = (lsops->files ? lsops->files : ft_lstcreate(".", 2));
		file_size = ft_lstsize(lst);
		while (lst)
		{
			files = ls_getfiles((char *)lst->content, getcmpfunc(lsops), lsops);
			if (!files)
				ft_printf_fd(2, "ft_ls: %s: %s\n", lst->content,
						strerror(errno));
			else
			{
				if (file_size > 1)
					ft_printf("%s:\n", lst->content);
				listfiles(files, lsops);
			}
			if (lst->next)
				ft_printf("\n");
			lst = lst->next;
		}
		ft_timefdel(&lsops->current);
	}
	ft_lstdel(&lsops->files, NULL);
	free(lsops);
	return (0);
}
