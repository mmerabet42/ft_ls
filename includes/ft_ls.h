/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/17 18:35:52 by mmerabet          #+#    #+#             */
/*   Updated: 2018/01/22 17:02:55 by mmerabet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include <sys/stat.h>

# include "ft_list.h"
# include "ft_btree.h"
# include "ft_time.h"

# define LSF_L		(1 << 0)
# define LSF_R_M	(1 << 1)
# define LSF_A		(1 << 2)
# define LSF_R		(1 << 3)
# define LSF_T		(1 << 4)
# define LSF_G_M	(1 << 5)
# define LSF_1		(1 << 6)
# define LSF_T_M	(1 << 7)
# define LSFLAGS	"lRartG1T"

typedef struct		s_lsops
{
	char			err;
	int				options;
	t_list			*files;
	t_timef			*current;
	t_cmpfunc		sortfunc;
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

typedef struct		s_print_info
{
	int				widths[8];
	int				ws_col;
	int				n;
	unsigned long	blocks;
	const t_btree	*files;
	const t_btree	*last_file;
	const t_lsops	*lsops;
}					t_print_info;

t_lsops				*ls_getlsops(int argc, char **argv);
void				ls_lsopsdel(t_lsops **lsops);

void				ls_listfiles(t_btree *files, const t_lsops *lsops);

t_file				*ls_getfile(const char *path);
t_btree				*ls_getfiles(const char *path,
							int hidden_files,
							t_cmpfunc sortfunc);

void				ls_filedel(t_file **file);
void				ls_getmodes(struct stat file_stat,
							const char *path,
							char *buffer);
char				*ls_getgrpname(gid_t gid);
char				*ls_getusrname(uid_t uid);

char				*ls_file_fg(t_file *file);
char				*ls_file_bg(t_file *file);
void				ls_getinfos(t_btree *files,
							const t_lsops *lsops,
							t_print_info *pinfo);

void				ls_printlong(t_btree *files, const t_lsops *lsops);
void				ls_printnormal(t_btree *file, const t_lsops *lsops);

int					ls_isfar(t_timef *a, t_timef *b);

int					ls_cmpfile_name(const void *a, const void *b, size_t n);
int					ls_cmpfile_time(const void *a, const void *b, size_t n);

#endif
