/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_formatfiles.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/15 14:44:30 by mmerabet          #+#    #+#             */
/*   Updated: 2018/01/21 17:57:02 by mmerabet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include "ft_mem.h"
#include "ft_math.h"
#include "ft_types.h"
#include "ft_str.h"
#include <sys/ioctl.h>
#include <unistd.h>

int				ls_isfar(t_timef *a, t_timef *b)
{
	int	fa;
	int	fb;
	int	m;

	if (!a || !b)
		return (0);
	m = (int)a->year - (int)b->year;
	fa = (int)a->month + (m > 0 ? 12 * ft_abs(m) : 0);
	fb = (int)b->month + (m < 0 ? 12 * ft_abs(m) : 0);
	if (fa - fb > 6 || fa - fb < -6)
		return (1);
	return (0);
}

static void		iter_getwidths(t_btree *bt, t_print_info *pinfo)
{
	t_file	*f;

	f = (t_file *)bt->content;
	pinfo->widths[0] = ft_max(pinfo->widths[0], ft_uintlen(f->fst.st_nlink));
	pinfo->widths[1] = ft_max(pinfo->widths[1],
			ft_strlen(f->usr_name ? f->usr_name : "(null)"));
	pinfo->widths[2] = ft_max(pinfo->widths[2],
			ft_strlen(f->grp_name ? f->grp_name : "(null)"));
	pinfo->widths[3] = ft_max(pinfo->widths[3], ft_ulonglen(f->fst.st_size));
	pinfo->widths[4] = ft_max(pinfo->widths[4], ft_strlen(f->name));
	pinfo->widths[5] = ft_max(pinfo->widths[5], ft_uintlen(f->major));
	pinfo->widths[6] = ft_max(pinfo->widths[6], ft_uintlen(f->minor));
	if (f->modes[0] == 'c' || f->modes[0] == 'b')
		pinfo->widths[7] = 8;
	pinfo->widths[7] = ft_max(pinfo->widths[7], pinfo->widths[3]);
	pinfo->blocks += f->fst.st_blocks;
}

void			ls_getinfos(t_btree *files, const t_lsops *lsops,
						t_print_info *pinfo)
{
	struct winsize	w;

	ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
	ft_bzero(pinfo, sizeof(t_print_info));
	pinfo->files = files;
	pinfo->last_file = ft_btree_right(files);
	pinfo->lsops = lsops;
	pinfo->ws_col = w.ws_col;
	ft_btree_iter_d(files, (void(*)(t_btree *, void *))iter_getwidths, pinfo);
}

char			*ls_file_fg(t_file *file)
{
	if (file->modes[0] == '-' && (file->modes[3] == 'x' ||
				file->modes[6] == 'x' || file->modes[9] == 'x'))
		return ("red");
	else if (file->modes[0] == 'd')
		return ("lgreen");
	else if (file->modes[0] == 'l')
		return ("lyellow");
	else if (file->modes[0] == 'c' || file->modes[0] == 'b')
		return ("black");
	else if (file->modes[0] == 's' || file->modes[0] == 'p')
		return ("pink");
	else if (file->name[0] == '.')
		return ("lblue");
	return ("white");
}

char			*ls_file_bg(t_file *file)
{
	if (file->modes[0] == 'c')
		return ("lyellow");
	else if (file->modes[0] == 'b')
		return ("lcyan");
	return ("-");
}
