/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_printlong.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/17 18:45:48 by mmerabet          #+#    #+#             */
/*   Updated: 2018/01/18 18:56:07 by mmerabet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include "ft_printf.h"

static char	*getsize(t_file *file, int widths[8])
{
	static char	*final;

	final = NULL;
	if (file->modes[0] == 'c' || file->modes[0] == 'b')
		ft_printf_s(&final, "%*u, %*u", 3, file->major,
				3, file->minor);
	else
		ft_printf_s(&final, "%*u", widths[3], file->fst.st_size);
	return (final);
}

static char	*gettime(t_file *file, const t_lsops *lsops)
{
	static char	*final;

	final = NULL;
	if (ls_isfar(file->mtime, lsops->current))
		ft_printf_s(&final, "%s %2u %5u", file->mtime->cmonth,
				file->mtime->day, file->mtime->year);
	else
		ft_printf_s(&final, "%s %2u %02u:%02u", file->mtime->cmonth,
				file->mtime->day, file->mtime->hour, file->mtime->min);
	return (final);
}

static void	printline(t_file *file, int wds[8], const t_lsops *lsops)
{
	int	b;
	int	d;

	if (!file)
		return ;
	b = lsops->options & LSF_G_M;
	d = lsops->options & LSF_T_M;
	ft_printf("%s %*lu %{%s}%-*s  %-*s%{%s}  %*s "
			"%{%s}%s%{%s} %{%s}%#{%s}%s%{%s}",
			file->modes, wds[0], file->fst.st_nlink, (b ? "lred" : "-"), wds[1],
			file->usr_name, wds[2], file->grp_name, (b ? "0" : "-"),
			wds[7], getsize(file, wds), (b ? "cyan" : "-"),
			gettime(file, lsops), (b ? "0" : "-"), (b ? ls_file_fg(file) : "-"),
			(b ? ls_file_bg(file) : "-"), (d ? file->full_name : file->name),
			(b ? "0" : "-"));
	if (file->link_name[0])
		ft_printf(" -> %s", file->link_name);
	ft_printf("\n");
}

void		ls_printlong(t_list *files, const t_lsops *lsops)
{
	int		widths[8];

	ft_printf("total %lu\n", ls_getwidths(widths, files));
	while (files)
	{
		printline((t_file *)files->content, widths, lsops);
		files = files->next;
	}
}

