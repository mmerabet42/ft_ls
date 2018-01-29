/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strpbrk.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/11 14:20:22 by mmerabet          #+#    #+#             */
/*   Updated: 2018/01/11 14:37:06 by mmerabet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_str.h"

char	*ft_strpbrk(const char *s, const char *charset)
{
	if (!s || !charset)
		return (NULL);
	while (*s)
	{
		if (ft_strchr(charset, *s))
			return ((char *)s);
		++s;
	}
	return (NULL);
}

int		ft_strpbrk_pos(const char *s, const char *charset)
{
	int	i;

	if (!s || !charset)
		return (-1);
	i = 0;
	while (s[i])
	{
		if (ft_strchr(charset, s[i]))
			return (i);
		++i;
	}
	return (-1);
}
