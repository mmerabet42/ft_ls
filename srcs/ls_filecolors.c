/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_filescolor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/23 18:50:39 by mmerabet          #+#    #+#             */
/*   Updated: 2018/01/23 19:17:45 by mmerabet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static t_locale_color	*def_locale = {
	{"white", "red", "lgreen", "lyellow", "black", "magenta", "lblue",
		NULL, NULL, NULL, NULL},
	{"-", "lyellow", "lcyan", NULL, NULL, 
};
static t_locale_color	*cur_locale = def_locale;

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
		return ("magenta");
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
