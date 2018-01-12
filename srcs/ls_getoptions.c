/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_getoptions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/11 18:07:29 by mmerabet          #+#    #+#             */
/*   Updated: 2018/01/12 20:29:18 by mmerabet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include "ft_str.h"
#include "ft_mem.h"
#include "ft_list.h"

static int		get_flag(char c)
{
	if (c == 'l')
		return (LSF_L);
	else if (c == 'R')
		return (LSF_R_M);
	else if (c == 'a')
		return (LSF_A);
	else if (c == 'r')
		return (LSF_R);
	else if (c == 't')
		return (LSF_T);
	return (0);
}

static int		ls_get_flags(int argc, char **argv, t_lsops *lsops)
{
	int	i;
	int	j;

	i = 1;
	while (i < argc)
	{
		if (argv[i][0] == '-')
		{
			j = 1;
			while (argv[i][j])
			{
				if (ft_strpbrk_pos(&argv[i][j], LSFLAGS) != 0)
					return ((int)(lsops->err = argv[i][j]));
				lsops->options |= get_flag(argv[i][j]);
				++j;
			}
		}
		else
			break;
		++i;
	}
	return (i);
}

static void		ls_get_files(int argc, char **argv, int istart, t_lsops *lsops)
{
	t_list	*tmp;

	while (istart < argc)
	{
		tmp = ft_lstpush(lsops->files,
				ft_lstcreate(argv[istart], ft_strlen(argv[istart]) + 1));
		if (!lsops->files)
			lsops->files = tmp;
		++istart;
	}
}

t_lsops			*ls_getoptions(int argc, char **argv)
{
	t_lsops	*lsops;
	int		i;

	if (!(lsops = (t_lsops *)ft_memalloc(sizeof(t_lsops))))
		return (NULL);
	i = ls_get_flags(argc, argv, lsops);
	if (!lsops->err)
		ls_get_files(argc, argv, i, lsops);
	return (lsops);
}
