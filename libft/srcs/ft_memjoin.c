/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/18 17:38:02 by mmerabet          #+#    #+#             */
/*   Updated: 2017/12/19 20:10:16 by mmerabet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_mem.h"

void	*ft_memjoin(const void *a,
				size_t an,
				const void *b,
				size_t bn)
{
	void	*s;

	if (!(s = malloc(an + bn)))
		return (NULL);
	if (a)
		ft_memcpy(s, a, an);
	if (b)
		ft_memcpy(s + an, b, bn);
	return (s);
}

void	*ft_memjoin_clr(void *a,
					size_t an,
					void *b,
					size_t bn)
{
	void	*s;

	if (!(s = malloc(an + bn)))
		return (NULL);
	if (a)
		ft_memcpy(s, a, an);
	if (b)
		ft_memcpy(s + an, b, bn);
	free(a);
	return (s);
}
