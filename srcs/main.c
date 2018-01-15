/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/12 18:57:45 by mmerabet          #+#    #+#             */
/*   Updated: 2018/01/15 19:22:51 by mmerabet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include "libft.h"
#include <fcntl.h>
#include <time.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>

void		getcmpfunc(t_lsops *lsops)
{
	if (lsops->options & LSF_T)
		lsops->sortfunc = ls_cmpfile_time;
	else
		lsops->sortfunc = ls_cmpfile_name;
}

void		listfiles(t_btree *files, const t_lsops *lsops)
{
	t_list	*lst;
	t_file	*file;

	if (!files || !lsops)
		return ;
	lst = (lsops->options & LSF_R ? ft_btree_tolistv(files) :
			ft_btree_tolist(files));
	if (lsops->options & LSF_L)
		ls_printlong(lst, lsops);
	else
		ls_printnormal(lst, lsops);
	if (lsops->options & LSF_R_M)
	{
		while (lst)
		{
			if ((file = (t_file *)lst->content) && file->modes[0] == 'd')
			{
				ft_printf("%s:\n", file->full_name);
				files = ls_getfiles(file->full_name, lsops);
				if (!files)
					ft_printf_fd(2, "ft_ls: %s: %s\n", file->full_name,
							strerror(errno));
				else
					listfiles(files, lsops);
			}
			lst = lst->next;
		}
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
		getcmpfunc(lsops);
		file_size = ft_lstsize(lst);
		while (lst)
		{
			files = ls_getfiles((char *)lst->content, lsops);
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
				ft_printf("\n\n");
			lst = lst->next;
		}
		ft_timefdel(&lsops->current);
	}
	ft_lstdel(&lsops->files, NULL);
	free(lsops);
	return (0);
}
