/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_cmpfile.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/13 22:50:33 by mmerabet          #+#    #+#             */
/*   Updated: 2018/01/18 15:02:09 by mmerabet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include "ft_str.h"
#include "ft_printf.h"

int	ls_cmpfile_name(const void *a, const void *b, size_t n)
{
	(void)n;
	return (ft_strcmp(((t_file *)a)->name, ((t_file *)b)->name));
}

int	ls_cmpfile_time(const void *a, const void *b, size_t n)
{
	t_file	*fa;
	t_file	*fb;

	(void)n;
	fa = (t_file *)a;
	fb = (t_file *)b;
	if (fa->mtime->full == fb->mtime->full)
		return (ft_strcmp(fa->name, fb->name));
	return (fb->mtime->full - fa->mtime->full);
}
