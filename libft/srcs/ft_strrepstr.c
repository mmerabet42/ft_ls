/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strreplacestr.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/12 16:57:56 by mmerabet          #+#    #+#             */
/*   Updated: 2017/12/19 21:51:02 by mmerabet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_str.h"

static void	ft_setlens(const char *s, const char *a, const char *b, int *lens)
{
	lens[0] = ft_strlen(a);
	lens[1] = ft_strlen(b);
	lens[2] = ft_strcountstr(s, a);
	lens[2] = ft_strlen(s) - (lens[0] * lens[2]) + (lens[1] * lens[2]);
}

char		*ft_strrepstr(const char *s, const char *a, const char *b)
{
	char	*snew;
	char	*pos;
	int		lens[3];

	if (!s || !a || !b)
		return (NULL);
	ft_setlens(s, a, b, lens);
	if ((snew = (char *)malloc(sizeof(char) * (lens[2] + 1))) == NULL)
		return (NULL);
	snew[lens[2]] = '\0';
	pos = ft_strstr(s, a);
	while (*s)
	{
		if (s == pos)
		{
			ft_strcpy(snew, b);
			snew += lens[1];
			s += lens[0];
			pos = ft_strstr(s, a);
		}
		else
			*snew++ = *s++;
	}
	return (snew - lens[2]);
}

char		*ft_strrepstr_clr(char *s, const char *a, const char *b)
{
	char	*snew;
	char	*pos;
	int		lens[3];

	ft_setlens(s, a, b, lens);
	if ((snew = (char *)malloc(sizeof(char) * (lens[2] + 1))) == NULL)
		return (NULL);
	snew[lens[2]] = '\0';
	pos = ft_strstr(s, a);
	while (*s)
	{
		if (s == pos)
		{
			ft_strcpy(snew, b);
			snew += lens[1];
			s += lens[0];
			pos = ft_strstr(s, a);
		}
		else
			*snew++ = *s++;
	}
	free(s);
	return (snew - lens[2]);
}
