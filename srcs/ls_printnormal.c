/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_printnormal.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/17 18:46:51 by mmerabet          #+#    #+#             */
/*   Updated: 2018/01/28 18:51:19 by mmerabet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include "ft_printf.h"
#include "ft_str.h"

static void	printline(t_btree *bt, t_print_info *pinfo)
{
	int		o;
	int		*ws;
	t_file	*file;
	int		islast;

	islast = (bt == pinfo->last_file);
	ws = pinfo->widths;
	file = (t_file *)bt->content;
	o = pinfo->lsops->options;
	ft_printf("%{%s}%#{%s}%s%{%s}",
			(o & (LSF_Y_M | LSF_G_M) ? ls_file_fg(file) : "-"),
			(o & (LSF_Y_M | LSF_G_M) ? ls_file_bg(file) : "-"),
			file->dname, (o & (LSF_Y_M | LSF_G_M) ? "0" : "-"));
	if (((pinfo->n += ws[4] + (!islast ? 1 : 0)) + ws[4] >= pinfo->ws_col
			&& !islast) || o & LSF_1)
	{
		ft_printf("\n");
		pinfo->n = 0;
	}
	else if (!(o & LSF_1) && !islast)
		ft_printf("%?*c", ws[4] - ft_strlen(file->dname) + 1, ' ');
}

void		ls_printnormal(t_btree *files, const t_lsops *lsops)
{
	t_print_info	pinfo;

	ls_getinfos(files, lsops, &pinfo);
	if (lsops->options & LSF_R)
		ft_btree_iterv_d(files, (void(*)(t_btree *, void *))printline, &pinfo);
	else
		ft_btree_iter_d(files, (void(*)(t_btree *, void *))printline, &pinfo);
	ft_printf((lsops->options & LSF_1) ? "" : "\n");
}
