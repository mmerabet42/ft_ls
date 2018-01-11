#include "ft_ls.h"
#include "libft.h"
#include <fcntl.h>
#include <errno.h>
#include <string.h>

int	main(int argc, char **argv)
{
	t_lsops			*lsops;
	t_list			*lst;
	int				fd;
	struct stat		fst;
	char			modes_buffer[12];
	char			*grp_name;
	char			*usr_name;

	if (!(lsops = ls_getoptions(argc, argv)))
		return (0);
	if (lsops->err)
		ft_printf("ft_ls: illegal option -- %c\n"
				"usage: ls [%s] [file ...]\n", lsops->err, LSFLAGS);
	else
	{
		lst = lsops->files;
		ft_bzero(modes_buffer, 12);
		while (lst)
		{
			if ((fd = open((char *)lst->content, O_RDONLY)) == -1)
				ft_printf("ft_ls: %s: %s\n", lst->content, strerror(errno));
			if (lstat((char *)lst->content, &fst) != -1)
			{
				ls_getmodes(fst, (char *)lst->content, modes_buffer);
				ls_getnames(fst, &grp_name, &usr_name);
				ft_printf("'%s' mode : '%s' %ld %s %s %lu\n", lst->content,
						modes_buffer, fst.st_nlink, grp_name, usr_name,
						fst.st_size);
			}
			lst = lst->next;
		}
	}
	ft_lstdel(&lsops->files, NULL);
	free(lsops);
	return (0);
}
