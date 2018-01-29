/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_math.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/19 18:41:25 by mmerabet          #+#    #+#             */
/*   Updated: 2018/01/11 17:04:25 by mmerabet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MATH_H
# define FT_MATH_H

typedef double	(*t_calcfunc)(double a, double b);

int					ft_abs(int n);
double				ft_absf(double n);

int					ft_pow(int x, int y);
int					ft_sqrt(int n);

int					ft_max(int a, int b);
int					ft_min(int a, int b);

#endif
