/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_cmpfile.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/13 22:50:33 by mmerabet          #+#    #+#             */
/*   Updated: 2018/01/27 18:40:35 by mmerabet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include "ft_str.h"

int	ls_cmpfile_name(const void *a, const void *b, size_t n)
{
	(void)n;
	return (ft_strcmp(((t_file *)a)->full_name, ((t_file *)b)->full_name));
}

int	ls_cmpfile_mtime(const void *a, const void *b, size_t n)
{
	const t_file	*fa;
	const t_file	*fb;

	(void)n;
	fa = (const t_file *)a;
	fb = (const t_file *)b;
	if (fa->mtime->full == fb->mtime->full)
		return (ft_strcmp(fa->name, fb->name));
	return ((int)fb->mtime->full - (int)fa->mtime->full);
}

int	ls_cmpfile_atime(const void *a, const void *b, size_t n)
{
	const t_file	*fa;
	const t_file	*fb;

	(void)n;
	fa = (const t_file *)a;
	fb = (const t_file *)b;
	if (fa->atime->full == fb->atime->full)
		return (ft_strcmp(fa->name, fb->name));
	return ((int)fb->atime->full - (int)fa->atime->full);
}

int	ls_cmpfile_btime(const void *a, const void *b, size_t n)
{
	const t_file	*fa;
	const t_file	*fb;

	(void)n;
	fa = (const t_file *)a;
	fb = (const t_file *)b;
	if (fa->btime->full == fb->btime->full)
		return (ft_strcmp(fa->name, fb->name));
	return ((int)fb->btime->full - (int)fa->btime->full);
}

int	ls_cmpfile_size(const void *a, const void *b, size_t n)
{
	const t_file	*fa;
	const t_file	*fb;

	(void)n;
	fa = (const t_file *)a;
	fb = (const t_file *)b;
	return (fb->fst.st_size - fa->fst.st_size);
}
