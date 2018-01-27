/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_filescolor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/23 18:50:39 by mmerabet          #+#    #+#             */
/*   Updated: 2018/01/27 17:39:50 by mmerabet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include "ft_mem.h"
#include "ft_printf_ext.h"

static t_locale_color		g_cur_locale = {
	{"bold/;0;255;145", "lyellow", "magenta", "magenta", "lred", "black",
		"blue", "red", "red", "black", "black", "lblue"},
	{"-", "-", "-", "-", "-", "lcyan", "lyellow", "-", "-", ";0;255;145",
		"lyellow", "-"}
};

static const t_color_attr	g_lscolors[] = {
	{"x", "-", "-"}, {"a", "bold/black", "black"}, {"b", "bold/red", "red"},
	{"c", "bold/green", "green"}, {"d", "bold/;204;204;0", ";204;204;0"},
	{"e", "bold/blue", "blue"}, {"f", "bold/magenta", "magenta"},
	{"g", "bold/cyan", "cyan"}, {"h", "bold/lgrey", "lgrey"}
};
static const size_t			g_lscolors_len =
sizeof(g_lscolors) / sizeof(t_color_attr);

static char			*ls_file_ext(t_file *file, char *gc[12])
{
	if (file->modes[0] == '-' && (file->modes[3] == 'x' ||
				file->modes[6] == 'x' || file->modes[9] == 'x'))
	{
		if (file->fst.st_mode & S_ISUID)
			return (gc[7]);
		else if (file->fst.st_mode & S_ISGID)
			return (gc[8]);
		return (gc[4]);
	}
	else if (file->modes[0] == 'd')
	{
		if (file->modes[8] == 'w' && file->fst.st_mode & S_ISVTX)
			return (gc[9]);
		else if (file->modes[8] == 'w' && !(file->fst.st_mode & S_ISVTX))
			return (gc[10]);
		return (gc[0]);
	}
	return (NULL);
}

char				*ls_file_fg(t_file *file)
{
	char	*nm;

	if ((nm = ls_file_ext(file, g_cur_locale.fg)))
		return (nm);
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

char				*ls_file_bg(t_file *file)
{
	char	*nm;

	if ((nm = ls_file_ext(file, g_cur_locale.bg)))
		return (nm);
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

const t_color_attr	*get_lscolor(char c, int *lr)
{
	size_t	i;

	i = 0;
	while (i < g_lscolors_len)
	{
		if (c == g_lscolors[i].name[0] || c + 32 == g_lscolors[i].name[0])
		{
			if (c == g_lscolors[i].name[0])
				*lr = 0;
			else
				*lr = 1;
			return (&g_lscolors[i]);
		}
		++i;
	}
	return (NULL);
}

void				ls_setlocale_color(const char *code)
{
	size_t				n;
	size_t				x;
	int					lr;
	const t_color_attr	*c;

	n = 1;
	x = 0;
	ft_bzero(&g_cur_locale, sizeof(t_locale_color));
	while (*code)
	{
		if ((c = get_lscolor(*code, &lr)))
		{
			if (n == 1)
				g_cur_locale.fg[x] = (!lr ? c->fg_cd : c->bg_cd);
			else if (n == 2)
				g_cur_locale.bg[x] = (!lr ? c->fg_cd : c->bg_cd);
		}
		++code;
		if (++n == 3)
		{
			++x;
			n = 1;
		}
	}
}
