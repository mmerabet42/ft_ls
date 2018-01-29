/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 20:00:41 by mmerabet          #+#    #+#             */
/*   Updated: 2017/12/20 20:38:50 by mmerabet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_types.h"
#include "ft_str.h"
#include "ft_math.h"

int	ft_atoi(const char *s)
{
	int					nb;
	int					sign;
	unsigned long long	max;

	nb = 0;
	max = 0;
	sign = 1;
	while (ft_isspace(*s))
		++s;
	if ((*s == '+' || *s == '-') && *s++ == '-')
		sign = -1;
	while (ft_isdigit(*s))
	{
		max = max * 10 + (*s - 48);
		if (sign == 1 && max >= 9223372036854775807)
			return (-1);
		else if (sign == -1 && max > 9223372036854775807)
			return (0);
		nb = nb * 10 + (*s++ - 48);
	}
	return (nb * sign);
}

int	ft_atoi_base(const char *s, const char *base)
{
	int	nb;
	int	baselen;
	int	sign;
	int	pos;
	int	i;

	if (!s || !base)
		return (0);
	baselen = ft_strlen(base);
	i = ft_strlen(s);
	nb = 0;
	sign = 1;
	while (ft_isspace(*s))
		++s;
	if ((*s == '+' || *s == '-') && *s++ == '-')
		sign = -1;
	while ((pos = ft_strchr_pos(base, *s++)) != -1)
		nb += pos * ft_pow(baselen, --i);
	return (nb * sign);
}
