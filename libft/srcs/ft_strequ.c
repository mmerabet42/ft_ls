/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strequ.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 22:36:07 by mmerabet          #+#    #+#             */
/*   Updated: 2017/12/19 21:37:45 by mmerabet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_str.h"

int	ft_strequ(const char *a, const char *b)
{
	if (!a || !b)
		return (0);
	while (*a || *b)
		if (*a++ != *b++)
			return (0);
	return (1);
}

int	ft_strnequ(const char *a, const char *b, size_t n)
{
	if (!a || !b)
		return (0);
	while (n-- && (*a || *b))
		if (*a++ != *b++)
			return (0);
	return (1);
}
