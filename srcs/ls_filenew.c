/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_filenew.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/12 23:02:02 by mmerabet          #+#    #+#             */
/*   Updated: 2018/01/12 23:14:33 by mmerabet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include "ft_mem.h"
#include <fcntl.h>

t_file	*ls_filenew(const char *file_name)
{
	t_file		*f;
	struct stat	fst;

	if (!file_name || lstat(file_name, &fst) == -1
			|| !(f = ft_memalloc(sizeof(t_file))))
		return (NULL);
	if ((f->fd = open(fle_name, O_RDONLY)))
	return (f);
}
