/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmatch.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/11 16:02:15 by mmerabet          #+#    #+#             */
/*   Updated: 2018/01/11 16:02:42 by mmerabet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_str.h"

static int	check_char(const char **str, const char **match)
{
	if (**str != **match)
		return (0);
	++(*str);
	++(*match);
	return (1);
}

int			ft_strmatch(const char *str, const char *match)
{
	while (*match)
	{
		if (*match == '*')
		{
			++match;
			if (*match == '*')
			{
				if (!check_char(&str, &match))
					return (0);
				continue;
			}
			if (!*match)
				return (1);
			while (*str && *str != *match)
				++str;
			if (!*str)
				return (0);
		}
		else if (!check_char(&str, &match))
			return (0);
	}
	return (*str ? 0 : 1);
}
