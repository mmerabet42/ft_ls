/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_cmpfile.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/13 22:50:33 by mmerabet          #+#    #+#             */
/*   Updated: 2018/01/13 22:56:14 by mmerabet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int	ls_cmpfile_name(const void *a, const void *b, size_t n)
{
	return (ft_strcmp(((t_file *)a)->name, ((t_file *)b)->name));
}

int	ls_cmpfile_time(const void *a, const void *b, size_t n)
{
	return (((t_file *)a)->mtime->full - ((t_file *)b)->mtime->full);
}
