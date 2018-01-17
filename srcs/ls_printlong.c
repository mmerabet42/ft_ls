/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_printlong.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/17 18:45:48 by mmerabet          #+#    #+#             */
/*   Updated: 2018/01/17 19:22:09 by mmerabet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include "ft_printf.h"

static char	*printsize(t_file *file, int widths[7])
{
	static char	*final;

	if (file->modes[0] == 'c' || file->modes[0] == 'b')
		ft_printf_s(&final, "%*u, %*u", widths[5], file->major,
				3, file->minor);
	else
		ft_printf_s(&final, "%*u", widths[3], file->fst.st_size);
	return (final);
}

static void	printline(t_file *file, int wds[7], const t_lsops *lsops)
{
	int	b;

	if (!file)
		return ;
	b = lsops->options & LSF_G_M;
	ft_printf("%s %*lu %{%s}%-*s  %-*s%{%s}  %s "
			"%{%s}%s %2u %02u:%02u%{%s} %{%s}%#{%s}%s%{%s}",
			file->modes, wds[0], file->fst.st_nlink, (b ? "lred" : "-"), wds[1],
			file->usr_name, wds[2], file->grp_name, (b ? "0" : "-"),
			printsize(file, wds), (b ? "cyan" : "-"), file->mtime->cmonth,
			file->mtime->day, file->mtime->hour, file->mtime->min,
			(b ? "0" : "-"), (b ? ls_file_fg(file) : "-"),
			(b ? ls_file_bg(file) : "-"), file->name, (b ? "0" : "-"));
	if (file->link_name[0])
		ft_printf(" -> %s", file->link_name);
	ft_printf("\n");
}

void		ls_printlong(t_list *files, const t_lsops *lsops)
{
	int		wds[7];

	ft_printf("total %lu\n", ls_getwidths(wds, files));
	while (files)
	{
		printline((t_file *)files->content, wds, lsops);
		files = files->next;
	}
}

