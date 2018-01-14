/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_cmpfile.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/13 22:50:33 by mmerabet          #+#    #+#             */
/*   Updated: 2018/01/14 18:23:09 by mmerabet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include "ft_str.h"

int	ls_cmpfile_name(const void *a, const void *b, size_t n)
{
	(void)n;
	return (ft_strcmp(((t_file *)a)->name, ((t_file *)b)->name));
}

int	ls_cmpfile_time(const void *a, const void *b, size_t n)
{
	t_timef	*fa;
	t_timef	*fb;

	(void)n;
	fa = ((t_file *)a)->mtime;
	fb = ((t_file *)b)->mtime;
	if (fa->year != fb->year)
		return ((int)(fb->year - fa->year));
	else if (fa->month != fb->month)
		return ((int)(fb->month - fa->month));
	else if (fa->day != fb->day)
		return ((int)(fb->day - fa->day));
	else if (fa->hour != fb->hour)
		return ((int)(fb->hour - fa->hour));
	else if (fa->min != fb->min)
		return ((int)(fb->min - fa->min));
	else if (fa->sec != fb->sec)
		return ((int)(fb->sec - fa->sec));
	return (0);
}
