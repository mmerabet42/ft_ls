/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_filescolor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/23 18:50:39 by mmerabet          #+#    #+#             */
/*   Updated: 2018/01/23 22:33:28 by mmerabet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include "ft_printf_ext.h"

static t_locale_color	g_cur_locale = {
	{"white", "red", "lgreen", "lyellow", "black", "magenta", "lblue",
		"-", "-", "-", "-", "-"},
	{"-", "lyellow", "lcyan", "-", "-", "-", "-", "-", "-", "-", "-", "-"}
};
static t_color_attr		g_lscolors[] = {
	{"a", "black", NULL}, {"b", "red", NULL}, {"c", "green", NULL},
	{"d", ";102;51;0", NULL}, {"e", "magenta", NULL}
}

char			*ls_file_fg(t_file *file)
{
	if (file->modes[0] == '-' && (file->modes[3] == 'x' ||
				file->modes[6] == 'x' || file->modes[9] == 'x'))
		return (cur_locale.fg[1]);
	else if (file->modes[0] == 'd')
		return (cur_locale.fg[2]);
	else if (file->modes[0] == 'l')
		return (cur_locale.fg[3]);
	else if (file->modes[0] == 'c' || file->modes[0] == 'b')
		return (cur_locale.fg[4]);
	else if (file->modes[0] == 's' || file->modes[0] == 'p')
		return (cur_locale.fg[5]);
	else if (file->name[0] == '.')
		return (cur_locale.fg[6]);
	return (cur_loacel.fg[0]);
}

char			*ls_file_bg(t_file *file)
{
	if (file->modes[0] == 'c')
		return ("lyellow");
	else if (file->modes[0] == 'b')
		return ("lcyan");
	return ("-");
}

void			ls_setlocale_color(const char *code)
{
	
}
