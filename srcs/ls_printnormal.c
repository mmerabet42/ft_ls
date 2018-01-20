/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_printnormal.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/17 18:46:51 by mmerabet          #+#    #+#             */
/*   Updated: 2018/01/20 19:51:34 by mmerabet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include "ft_printf.h"
#include "ft_str.h"

static void	printline(t_btree *bt, t_print_info *pinfo)
{
	int		b;
	int		c;
	int		*ws;
	t_file	*file;
	int		islast;

	islast = (bt == pinfo->last_file);
	ws = pinfo->widths;
	file = (t_file *)bt->content;
	b = pinfo->lsops->options & LSF_G_M;
	c = pinfo->lsops->options & LSF_1;
	ft_printf("%{%s}%#{%s}%s%{%s}%?*c%s", (b ? ls_file_fg(file) : "-"),
		(b ? ls_file_bg(file) : "-"), file->name, (b ? "0" : "-"),
		(!islast && !c ? ws[4] - ft_strlen(file->name) + 1 : 0), ' ',
		(c ? "\n" : ""));
	if ((pinfo->n += ws[4] + (!islast ? 1 : 0)) + ws[4] >= pinfo->ws_col
			&& !islast && !c)
	{
		ft_printf("\n");
		pinfo->n = 0;
	}
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
