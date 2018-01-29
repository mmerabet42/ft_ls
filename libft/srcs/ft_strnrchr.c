/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnrchr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 16:48:38 by mmerabet          #+#    #+#             */
/*   Updated: 2017/12/19 21:49:09 by mmerabet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_str.h"

char	*ft_strnrchr(const char *s, int c, size_t n)
{
	int		i;
	size_t	len;

	len = ft_strlen(s);
	if (n >= len)
		n = len - 1;
	i = n;
	while (i >= 0 && s[i] != c)
		--i;
	return ((char *)(s[i] == c ? &s[i] : NULL));
}
