/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_filescolor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/23 18:50:39 by mmerabet          #+#    #+#             */
/*   Updated: 2018/01/24 17:49:06 by mmerabet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include "ft_printf_ext.h"

static t_locale_color		g_cur_locale = {
	{"lgreen", "lyellow", "magenta", "magenta", "red", "black",
		"black", "red", "red", "lgreen", "lgreen", "-"},
	{"-", "-", "-", "-", "-", "lcyan", "lyellow", "-", "-", "-", "-", "-"}
};

static const t_color_attr	g_lscolors[] = {
	{"x", "-", "-"}, {"a", "bold/black", "black"}, {"b", "bold/red", "red"},
	{"c", "bold/green", "green"}, {"d", "bold/;204;204;0", ";204;204;0"},
	{"e", "bold/blue", "blue"}, {"f", "bold/magenta", "magenta"},
	{"g", "bold/cyan", "cyan"}, {"h", "bold/lgrey", "lgrey"},
};
static const size_t			g_lscolors_len = sizeof(g_lscolors) / sizeof(t_color_attr);

char			*ls_file_fg(t_file *file)
{
	if (file->modes[0] == '-' && (file->modes[3] == 'x' ||
				file->modes[6] == 'x' || file->modes[9] == 'x'))
		return (g_cur_locale.fg[4]);
	else if (file->modes[0] == 'd')
		return (g_cur_locale.fg[0]);
	else if (file->modes[0] == 'l')
		return (g_cur_locale.fg[1]);
	else if (file->modes[0] == 'c')
		return (g_cur_locale.fg[6]);
	else if (file->modes[0] == 'b')
		return (g_cur_locale.fg[5]);
	else if (file->modes[0] == 's')
		return (g_cur_locale.fg[2]);
	else if (file->modes[0] == 'p')
		return (g_cur_locale.fg[3]);
	else if (file->name[0] == '.')
		return (g_cur_locale.fg[11]);
	return ("-");
}

char			*ls_file_bg(t_file *file)
{
	if (file->modes[0] == '-' && (file->modes[3] == 'x' ||
				file->modes[6] == 'x' || file->modes[9] == 'x'))
		return (g_cur_locale.bg[4]);
	else if (file->modes[0] == 'd')
		return (g_cur_locale.bg[0]);
	else if (file->modes[0] == 'l')
		return (g_cur_locale.bg[1]);
	else if (file->modes[0] == 'c')
		return (g_cur_locale.bg[6]);
	else if (file->modes[0] == 'b')
		return (g_cur_locale.bg[5]);
	else if (file->modes[0] == 's')
		return (g_cur_locale.bg[2]);
	else if (file->modes[0] == 'p')
		return (g_cur_locale.bg[3]);
	else if (file->name[0] == '.')
		return (g_cur_locale.bg[11]);
	return ("-");
}

void			ls_setlocale_color(const char *code)
{
	size_t	i;
	int		n;
	int		x;

	n = 1;
	x = 0;
	while (*code)
	{
		i = 0;
		while (i < g_lscolors_len)
		{
			if (*code == g_lscolors[i].name[0])
			{
				if (n == 1)
					g_cur_locale.fg[x] = g_lscolors[i].fg_cd;
				else if (n == 2)
					g_cur_locale.bg[x] = g_lscolors[i].fg_cd;
				break ;
			}
			else if (*code + 32 == g_lscolors[i].name[0])
			{
				if (n == 1)
					g_cur_locale.fg[x] = g_lscolors[i].bg_cd;
				else if (n == 2)
					g_cur_locale.bg[x] = g_lscolors[i].bg_cd;
				break ;
			}
			++i;
		}
		++code;
		if (++n == 3)
		{
			++x;
			n = 1;
		}
	}
}
