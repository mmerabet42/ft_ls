/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/17 18:35:52 by mmerabet          #+#    #+#             */
/*   Updated: 2018/01/17 23:10:21 by mmerabet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include <sys/stat.h>

# include "ft_list.h"
# include "ft_btree.h"
# include "ft_time.h"

# define LSF_L		1
# define LSF_R_M	2
# define LSF_A		4
# define LSF_R		8
# define LSF_T		16
# define LSF_G_M	32
# define LSF_1		64
# define LSFLAGS "lRartG1"

typedef struct		s_lsops
{
	char			err;
	int				options;
	t_list			*files;
	t_timef			*current;
}					t_lsops;

typedef struct		s_file
{
	char			*name;
	char			*full_name;
	char			link_name[512];
	char			modes[12];
	char			*grp_name;
	char			*usr_name;
	unsigned int	major;
	unsigned int	minor;
	t_timef			*mtime;
	struct stat		fst;
	t_btree			*files;
}					t_file;

t_lsops				*ls_getoptions(int argc, char **argv);
t_file				*ls_getfile(const char *file_name);
t_btree				*ls_getfiles(const char *file_name,
							int hidden_files,
							t_cmpfunc sortfunc);
void				ls_filedel(t_file *f);
void				ls_getmodes(struct stat file_stat,
							const char *path,
							char *buffer);
char				*ls_getgrpname(gid_t gid);
char				*ls_getusrname(uid_t uid);

char				*ls_file_fg(t_file *file);
char				*ls_file_bg(t_file *file);
unsigned long		ls_getwidths(int widths[7], t_list *files);

void				ls_printlong(t_list *files, const t_lsops *lsops);
void				ls_printnormal(t_list *file, const t_lsops *lsops);

int					ls_isfar(t_timef *a, t_timef *b);

int					ls_cmpfile_name(const void *a, const void *b, size_t n);
int					ls_cmpfile_time(const void *a, const void *b, size_t n);

#endif
