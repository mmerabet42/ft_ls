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
# define LSFLAGS "lRart"

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
	char			*modes;
	char			*grp_name;
	char			*usr_name;
	int				isfar;
	t_timef			*mtime;
	struct stat		file_stat;
	t_btree			*childs;
}					t_file;

t_lsops				*ls_getoptions(int argc, char **argv);
t_file				*ls_filenew(const char *file_name,
							int childs,
							t_cmpfunc sortfunc);
void				ls_filedel(t_file *f);
void				ls_getmodes(struct stat file_stat,
							const char *path,
							char *buffer);
char				*ls_getgrpname(gid_t gid);
char				*ls_getusrname(uid_t uid);

int					ls_cmpfile_name(const void *a, const void *b, size_t n);
int					ls_cmpfile_time(const void *a, const void *b, size_t n);

#endif
