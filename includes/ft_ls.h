#ifndef FT_LS_H
# define FT_LS_H

# include <dirent.h>
# include <sys/types.h>
# include <sys/stat.h>

# include "ft_list.h"
# include "ft_btree.h"
# include "ft_time.h"

# define LSF_L 1
# define LSF_R_M 2
# define LSF_A 4
# define LSF_R 8
# define LSF_T 16
# define LSF_G_M 32
# define LSFLAGS "lRartG"

typedef struct		s_lsops
{
	char			err;
	int				options;
	t_cmpfunc		sortfunc;
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
	int				isfar;
	t_timef			*mtime;
	struct stat		fst;
	t_btree			*files;
}					t_file;

t_lsops				*ls_getoptions(int argc, char **argv);
t_file				*ls_getfile(const char *file_name, t_timef *current_time);
t_btree				*ls_getfiles(const char *file_name,
							const t_lsops *lsops);
void				ls_filedel(t_file *f);
void				ls_getmodes(struct stat file_stat,
							const char *path,
							char *buffer);
char				*ls_getgrpname(gid_t gid);
char				*ls_getusrname(uid_t uid);

void				ls_printlong(t_list *files, const t_lsops *lsops);
void				ls_printnormal(t_list *file, const t_lsops *lsops);

int					ls_cmpfile_name(const void *a, const void *b, size_t n);
int					ls_cmpfile_time(const void *a, const void *b, size_t n);

#endif
