#include "asm.h"

void	ft_error(t_env *env, char *str)
{
	ft_putstr_fd("\033[33m", 2);
	ft_putstr_fd(str, 2);
	if (env)
	{
		ft_putstr_fd(" at ", 2);
		ft_putstr_fd("line ", 2);
		ft_putstr_fd("\033[0m", 2);
		ft_putstr_fd("\033[35m", 2);
		if (env->nb_line)
			ft_putnbr_fd(env->nb_line, 2);
		ft_putstr_fd("\n\033[0m", 2);
		ft_putstr_fd("\033[33m", 2);
		if (env->line)
		{
			ft_putstr_fd(env->line, 2);
			ft_putstr_fd("\n", 2);
		}
		ft_putstr_fd("\033[0m", 2);
		// tafreetatoucompris(env);
	}
	exit(0);
}
