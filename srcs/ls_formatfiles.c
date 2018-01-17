/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_formatfiles.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/15 14:44:30 by mmerabet          #+#    #+#             */
/*   Updated: 2018/01/17 19:20:54 by mmerabet         ###   ########.fr       */
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
	if (!a || !b)
		return (0);
	if ((int)a->month < (int)b->month - 6 || (int)a->month > (int)b->month + 6)
		return (1);
	return (0);
}

unsigned long	ls_getwidths(int widths[7], t_list *lst)
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
			widths[5] = ft_max(widths[5], ft_uintlen(file->major));
			widths[6] = ft_max(widths[6], ft_uintlen(file->minor));
			blks += file->fst.st_blocks;
		}
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
		return ("blue");
	else if (file->name[0] == '.')
		return ("lblue");
	return ("white");
}

char			*ls_file_bg(t_file *file)
{
	if (file->modes[0] == 'c')
		return ("yellow");
	else if (file->modes[0] == 'b')
		return ("cyan");
	return ("-");
}
