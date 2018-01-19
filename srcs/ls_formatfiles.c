/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_formatfiles.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/15 14:44:30 by mmerabet          #+#    #+#             */
/*   Updated: 2018/01/19 17:36:04 by mmerabet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include "ft_mem.h"
#include "ft_math.h"
#include "ft_types.h"
#include "ft_str.h"
#include "ft_printf.h"

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

unsigned long	ls_getwidths(int ws[8], t_list *lst)
{
	t_list			*it;
	t_file			*f;
	unsigned long	blks;

	ft_bzero(ws, sizeof(int) * 8);
	it = lst;
	blks = 0;
	while (it)
	{
		f = (t_file *)it->content;
		ws[0] = ft_max(ws[0], ft_uintlen(f->fst.st_nlink));
		ws[1] = ft_max(ws[1], ft_strlen(f->usr_name ? f->usr_name : "(null)"));
		ws[2] = ft_max(ws[2], ft_strlen(f->grp_name ? f->grp_name : "(null)"));
		ws[3] = ft_max(ws[3], ft_ulonglen(f->fst.st_size));
		ws[4] = ft_max(ws[4], ft_strlen(f->name));
		ws[5] = ft_max(ws[5], ft_uintlen(f->major));
		ws[6] = ft_max(ws[6], ft_uintlen(f->minor));
		if (f->modes[0] == 'c' || f->modes[0] == 'b')
			ws[7] = 8;
		ws[7] = ft_max(ws[7], ws[3]);
		blks += f->fst.st_blocks;
		it = it->next;
	}
	return (blks);
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
