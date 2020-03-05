#include "libft.h"

void	ft_perror(char *error)
{
	ft_putstr_fd("\033[31m", 2);
	ft_putendl_fd(error, 2);
	ft_putstr_fd("\033[0m", 2);
	exit(0);
}
