/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/12 18:57:45 by mmerabet          #+#    #+#             */
/*   Updated: 2018/01/13 23:17:58 by mmerabet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include "libft.h"
#include <fcntl.h>
#include <time.h>
#include <string.h>
#include <errno.h>

int	main(int argc, char **argv)
{
	t_lsops			*lsops;
	t_list			*lst;
	int				fd;
	struct stat		fst;
	char			modes_buffer[12];
	t_timef			*tf;
	time_t			cur_t;

	if (!(lsops = ls_getoptions(argc, argv)))
		return (0);
	if (lsops->err)
		ft_printf("ft_ls: illegal option -- %c\n"
				"usage: ls [%s] [file ...]\n", lsops->err, LSFLAGS);
	else
	{
		cur_t = time(NULL);
		lsops.current = ft_timefnew(&cur_t);
		lst = lsops->files;
		ft_bzero(modes_buffer, 12);
		while (lst)
		{
			if ((fd = open((char *)lst->content, O_RDONLY)) == -1)
				ft_printf("ft_ls: %s: %s\n", lst->content, strerror(errno));
			if (lstat((char *)lst->content, &fst) != -1)
			{
				ls_getmodes(fst, (char *)lst->content, modes_buffer);
				tf = ft_timefnew(&fst.st_mtime);
				ft_printf("%s %ld %s %s %lu %s %u %u:%u %s %i\n",
						modes_buffer, fst.st_nlink,
						ls_getusrname(fst.st_uid), ls_getgrpname(fst.st_gid),
						fst.st_size,
						tf->cmonth, tf->day, tf->hour, tf->min,
						lst->content, ls_isfar(tf, cur));
				ft_timefdel(&tf);
			}
			lst = lst->next;
		}
		ft_timefdel(&cur);
	}
	ft_lstdel(&lsops->files, NULL);
	free(lsops);
	return (0);
}
