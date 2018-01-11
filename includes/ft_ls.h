#ifndef FT_LS_H
# define FT_LS_H

# include <dirent.h>
# include <sys/types.h>
# include <sys/stat.h>

# include "ft_list.h"

# define LSF_L 1
# define LSF_R_M 2
# define LSF_A 4
# define LSF_R 8
# define LSF_T 16
# define LSFLAGS "lRart"

typedef struct	s_lsops
{
	char		err;
	int			options;
	t_list		*files;
}				t_lsops;

t_lsops			*ls_getoptions(int argc, char **argv);
void			ls_getmodes(struct stat file_stat,
						const char *path,
						char *buffer);
void			ls_getnames(struct stat file_stat,
						char **grp_name,
						char **usr_name);

#endif
