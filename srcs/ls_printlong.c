/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_printlong.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/17 18:45:48 by mmerabet          #+#    #+#             */
/*   Updated: 2018/01/28 21:21:30 by mmerabet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include "ft_printf.h"

static char	*getsize(t_file *file, int widths[8])
{
	char	*final;

	final = NULL;
	if (file->modes[0] == 'c' || file->modes[0] == 'b')
		ft_printf_s(&final, "%*u, %*u", 3, file->major,
				3, file->minor);
	else
		ft_printf_s(&final, "%*lu", widths[3], file->fst.st_size);
	return (final);
}

static char	*gettime(t_file *file, const t_lsops *lsops)
{
	char	*final;
	char	*tmp;

	final = NULL;
	if (!(lsops->options & LSF_T_M) && ls_isfar(file->mtime, lsops->current))
		ft_printf_s(&final, "%s %2u %5u", file->mtime->cmonth,
				file->mtime->day, file->mtime->year);
	else
	{
		ft_printf_s(&final, "%s %2u %02u:%02u", file->mtime->cmonth,
				file->mtime->day, file->mtime->hour, file->mtime->min);
		if (lsops->options & LSF_T_M)
		{
			tmp = final;
			ft_printf_s(&final, "%s:%02u %u", final, file->mtime->sec,
					file->mtime->year);
			free(tmp);
		}
	}
	return (final);
}

static void	mainprint(t_file *file, int ws[8], int o, char *finals[2])
{
	ft_printf("%s %*lu %{%s}%-*s  %-*s%{%s}  %*s "
			"%{%s}%s%{%s} %{%s}%#{%s}%s%{%s}",
			file->modes, ws[0], file->fst.st_nlink,
			(o & LSF_Y_M ? "lred" : "-"), ws[1], file->usr_name, ws[2],
			file->grp_name, (o & LSF_Y_M ? "0" : "-"), ws[7], finals[0],
			(o & LSF_Y_M ? "cyan" : "-"), finals[1], (o & LSF_Y_M ? "0" : "-"),
			(o & (LSF_G_M | LSF_Y_M) ? ls_file_fg(file) : "-"),
			(o & (LSF_G_M | LSF_Y_M) ? ls_file_bg(file) : "-"),
			file->dname, (o & (LSF_G_M | LSF_Y_M) ? "0" : "-"));
	if (file->link_name[0])
		ft_printf(" -> %s", file->link_name);
	ft_printf("\n");
}

static void	printline(t_btree *bt, t_print_info *pinfo)
{
	t_file	*file;
	char	*finals[2];

	if (!(file = (t_file *)bt->content))
		return ;
	finals[0] = getsize(file, pinfo->widths);
	finals[1] = gettime(file, pinfo->lsops);
	mainprint(file, pinfo->widths, pinfo->lsops->options, finals);
	free(finals[0]);
	free(finals[1]);
}

void		ls_printlong(t_btree *files, const t_lsops *lsops)
{
	t_print_info pinfo;

	ls_getinfos(files, lsops, &pinfo);
	if (files != lsops->files)
		ft_printf("total %lu\n", pinfo.blocks);
	if (lsops->options & LSF_R)
		ft_btree_iterv_d(files, (void(*)(t_btree *, void *))printline, &pinfo);
	else
		ft_btree_iter_d(files, (void(*)(t_btree *, void *))printline, &pinfo);
}
