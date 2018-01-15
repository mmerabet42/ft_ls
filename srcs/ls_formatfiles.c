/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_formatfiles.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/15 14:44:30 by mmerabet          #+#    #+#             */
/*   Updated: 2018/01/15 19:16:12 by mmerabet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include "ft_mem.h"
#include "ft_math.h"
#include "ft_types.h"
#include "ft_str.h"
#include "ft_printf.h"
#include <sys/ioctl.h>
#include <unistd.h>

static void	getwidths(int widths[5], t_list *lst)
{
	t_list	*it;
	t_file	*file;

	ft_bzero(widths, sizeof(int) * 5);
	it = lst;
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
		}
		it = it->next;
	}
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

static char	*file_bg(t_file *file)
{
	(void)file;
	return ("");
}

void		ls_printlong(t_list *files, const t_lsops *lsops)
{
	int		wds[5];
	t_file	*f;
	int		b;

	getwidths(wds, files);
	b = lsops->options & LSF_G_M;
	while (files)
	{
		if ((f = (t_file *)files->content))
		{
			ft_printf("%s %*lu %{%s}%-*s  %-*s%{%s}  %*lu "
				"%{%s}%s %2u %02u:%02u%{%s} %{%s}%#{%s}%s%{%s}",
				f->modes, wds[0], f->fst.st_nlink, (b ? "lred" : "-"), wds[1],
				f->usr_name, wds[2], f->grp_name, (b ? "0" : "-"), wds[3],
				f->fst.st_size, (b ? "cyan" : "-"), f->mtime->cmonth,
				f->mtime->day, f->mtime->hour, f->mtime->min, (b ? "0" : "-"),
				(b ? file_fg(f) : "-"), (b ? file_bg(f) : "-"), f->name,
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
			ft_printf("%{%s}%#{%s}%-*s%{%s}%s", (b ? file_fg(file) : "-"),
					(b ? file_bg(file) : "-"), (files->next ? wds[4] : -1),
					file->name, (b ? "0" : "-"), (files->next ? " " : ""));
			if ((n += wds[4] + (files->next ? 1 : 0)) + wds[4] >= w.ws_col)
			{
				ft_printf("\n");
				n = 0;
			}
		}
		files = files->next;
	}
	ft_printf("\n");
}
