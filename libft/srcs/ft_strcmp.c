/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 19:43:06 by mmerabet          #+#    #+#             */
/*   Updated: 2017/12/19 20:49:02 by mmerabet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_str.h"

int	ft_strcmp(const char *a, const char *b)
{
	const unsigned char	*ua;
	const unsigned char	*ub;

	ua = (const unsigned char *)a;
	ub = (const unsigned char *)b;
	while (*ua && *ub && (*ua == *ub))
	{
		++ua;
		++ub;
	}
	return ((int)(*ua - *ub));
}

int	ft_strncmp(const char *a, const char *b, size_t n)
{
	const unsigned char	*ua;
	const unsigned char *ub;

	ua = (const unsigned char *)a;
	ub = (const unsigned char *)b;
	while (n-- && (*ua || *ub))
	{
		if (*ua != *ub)
			return (*ua - *ub);
		++ua;
		++ub;
	}
	return (0);
}
