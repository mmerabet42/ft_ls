/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 15:48:48 by mmerabet          #+#    #+#             */
/*   Updated: 2017/12/19 20:43:04 by mmerabet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_str.h"

char	*ft_strcat(char *a, const char *b)
{
	size_t	i;

	if (!a || !b)
		return (NULL);
	i = ft_strlen(a);
	while (*b)
		a[i++] = *b++;
	a[i] = '\0';
	return (a);
}

char	*ft_strcatc(char *a, char b)
{
	a[ft_strlen(a)] = b;
	return (a);
}

size_t	ft_strlcat(char *a, const char *b, size_t n)
{
	size_t	alen;
	size_t	blen;
	size_t	i;

	alen = ft_strlen(a);
	blen = ft_strlen(b);
	if (n <= alen)
		return (n + blen);
	i = alen;
	while (*b && i < n - 1)
		a[i++] = *b++;
	a[i] = '\0';
	return (alen + blen);
}

char	*ft_strncat(char *a, const char *b, size_t n)
{
	size_t	i;
	size_t	j;

	i = ft_strlen(a);
	j = 0;
	while (j < n && b[j])
		a[i++] = b[j++];
	a[i] = '\0';
	return (a);
}
