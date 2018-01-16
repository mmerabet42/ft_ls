/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_formatfiles.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/15 14:44:30 by mmerabet          #+#    #+#             */
/*   Updated: 2018/01/16 23:27:21 by mmerabet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include "ft_mem.h"
#include "ft_math.h"
#include "ft_types.h"
#include "ft_str.h"
#include "ft_printf.h"
#include <sys/ioctl.h>
#include <sys/types.h>
#include <unistd.h>

static int	getwidths(int widths[7], t_list *lst)
{
	t_list			*it;
	t_file			*file;
	unsigned long	blks;

	ft_bzero(widths, sizeof(int) * 7);
	it = lst;
	blks = 0;
	while (it)
	{
		if ((file = (t_file *)it->content))
		{
			widths[0] = ft_max(widths[0], ft_uintlen(file->fst.st_nlink));
			widths[1] = ft_max(widths[1],
					ft_strlen(file->usr_name ? file->usr_name : "(null)"));
			widths[2] = ft_max(widths[2],
					ft_strlen(file->grp_name ? file->grp_name : "(null)"));
			widths[3] = ft_max(widths[3], ft_uintlen(file->fst.st_size));
			widths[4] = ft_max(widths[4], ft_strlen(file->name));
			widths[5] = ft_max(widths[5], ft_uintlen(major(file->fst.st_rdev)));
			widths[6] = ft_max(widths[6], ft_uintlen(minor(file->fst.st_rdev)));
			blks += file->fst.st_blocks;
		}
		it = it->next;
	}
	return (blks);
}

static char	*file_fg(t_file *file)
{
	if (file->modes[0] == '-' && (file->modes[3] == 'x' ||
				file->modes[6] == 'x' || file->modes[9] == 'x'))
		return ("red");
	else if (file->modes[0] == 'd')
		return ("lgreen");
	else if (file->modes[0] == 'l')
		return ("lyellow");
	else if (file->name[0] == '.')
		return ("lblue");
	return ("white");
}

static char				*printsize(t_file *file, int widths[7])
{
	static char	*final;
	int			mjr;
	int			mnr;

	mjr = major(file->fst.st_rdev);
	mnr = minor(file->fst.st_rdev);
	ft_printf_s(&final, "%*u, %*u", widths[5], mjr,
			widths[6], mnr);
	return (final);
}

void					ls_printlong(t_list *files, const t_lsops *lsops)
{
	int		wds[7];
	t_file	*f;
	int		b;

	b = lsops->options & LSF_G_M;
	ft_printf("total %lu\n", getwidths(wds, files));
	while (files)
	{
		if ((f = (t_file *)files->content))
		{
			ft_printf("%s %*lu %{%s}%-*s  %-*s%{%s}  %s "
				"%{%s}%s %2u %02u:%02u %u%{%s} %{%s}%s%{%s}",
				f->modes, wds[0], f->fst.st_nlink, (b ? "lred" : "-"), wds[1],
				f->usr_name, wds[2], f->grp_name, (b ? "0" : "-"),
				printsize(f, wds), (b ? "cyan" : "-"), f->mtime->cmonth,
				f->mtime->day, f->mtime->hour, f->mtime->min, f->mtime->year,
				(b ? "0" : "-"), (b ? file_fg(f) : "-"), f->name,
				(b ? "0" : "-"));
			if (f->link_name[0])
				ft_printf(" -> %s", f->link_name);
			ft_printf("\n");
		}
		files = files->next;
	}
}

void		ls_printnormal(t_list *files, const t_lsops *lsops)
{
	int				wds[5];
	t_file			*file;
	struct winsize	w;
	int				n;
	int				b;

	ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
	getwidths(wds, files);
	n = 0;
	b = lsops->options & LSF_G_M;
	while (files)
	{
		if ((file = (t_file *)files->content))
		{
			if ((n += wds[4] + (files->next ? 1 : 0)) >= w.ws_col
					&& files->next)
			{
				ft_printf("\n");
				n = 0;
			}
			ft_printf("%{%s}%-*s%{%s}%s", (b ? file_fg(file) : "-"),
					(files->next ? wds[4] : -1), file->name, (b ? "0" : "-"),
					(files->next ? " " : ""));
		}
		files = files->next;
	}
	ft_printf("\n");
}
