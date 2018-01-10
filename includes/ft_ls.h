#include "ft_list.h"
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>

typedef struct	s_lsops
{
	long long	option_bits;
	t_list		*files;
}				t_lsops;

t_lsops			ls_get_options(int argc, char **argv);
