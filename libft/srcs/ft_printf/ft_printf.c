/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/02 20:27:32 by mmerabet          #+#    #+#             */
/*   Updated: 2017/12/19 19:01:16 by mmerabet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int				ft_printf(const char *format, ...)
{
	va_list	args;
	int		ret;

	va_start(args, format);
	ret = ft_vprintf(format, args);
	va_end(args);
	return (ret);
}

int				ft_printf_fd(int fd, const char *format, ...)
{
	va_list	args;
	int		ret;

	va_start(args, format);
	ret = ft_vprintf_fd(fd, format, args);
	va_end(args);
	return (ret);
}

int				ft_printf_s(char **buffer, const char *format, ...)
{
	va_list	args;
	int		ret;

	va_start(args, format);
	ret = ft_vprintf_s(buffer, format, args);
	va_end(args);
	return (ret);
}
