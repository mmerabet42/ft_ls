/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 22:45:25 by mmerabet          #+#    #+#             */
/*   Updated: 2017/12/20 20:41:37 by mmerabet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_str.h"

char	*ft_strjoin(const char *a, const char *b)
{
	char	*s;

	if (!(s = ft_strnew(ft_strlen(a) + ft_strlen(b))))
		return (NULL);
	if (a)
		ft_strcat(s, a);
	if (b)
		ft_strcat(s, b);
	return (s);
}

char	*ft_strjoin_clr(char *a, char *b, int d)
{
	char	*s;

	if (!(s = ft_strnew(ft_strlen(a) + ft_strlen(b))))
		return (NULL);
	if (a)
		ft_strcat(s, a);
	if (b)
		ft_strcat(s, b);
	if (d == 2 || d == 0)
		free(a);
	if (d == 2 || d == 1)
		free(b);
	return (s);
}
