/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_printnormal.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/17 18:46:51 by mmerabet          #+#    #+#             */
/*   Updated: 2018/01/18 20:45:38 by mmerabet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include "ft_printf.h"
#include "ft_str.h"
#include <sys/ioctl.h>
#include <unistd.h>

static void	printline(t_list *files, t_file *file, int wds[8],
				const t_lsops *lsops)
{
	int	b;

	b = lsops->options & LSF_G_M;
	ft_printf("%{%s}%#{%s}%s%{%s}%?*c%s", (b ? ls_file_fg(file) : "-"),
		(b ? ls_file_bg(file) : "-"), file->name, (b ? "0" : "-"),
		(files->next && !(lsops->options & LSF_1)
			? wds[4] - ft_strlen(file->name) + 1 : 0), ' ',
		(lsops->options & LSF_1 ? "\n" : ""));
}

void		ls_printnormal(t_list *files, const t_lsops *lsops)
{
	int				wds[8];
	struct winsize	w;
	int				n;

	ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
	ls_getwidths(wds, files);
	n = 0;
	while (files)
	{
		printline(files, (t_file *)files->content, wds, lsops);
		if ((n += wds[4] + (files->next ? 1 : 0)) + wds[4] >= w.ws_col
				&& files->next && !(lsops->options & LSF_1))
		{
			ft_printf("\n");
			n = 0;
		}
		files = files->next;
	}
	ft_printf((lsops->options & LSF_1) ? "" : "\n");
}
