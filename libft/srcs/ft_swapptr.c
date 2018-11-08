/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_swapptr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/14 22:47:06 by mmerabet          #+#    #+#             */
/*   Updated: 2017/12/19 21:57:31 by mmerabet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_mem.h"

void	ft_swapptr(void **a, void **b)
{
	void	*tmp;

	if (!a || !b)
		return ;
	tmp = *a;
	*a = *b;
	*b = tmp;
}