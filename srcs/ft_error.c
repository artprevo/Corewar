/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artprevo <artprevo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/31 15:12:34 by artprevo          #+#    #+#             */
/*   Updated: 2020/08/02 13:42:20 by artprevo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	}
	exit(1);
}

void	ft_error2(char *str)
{
	ft_putstr_fd("\033[33m", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("\033[0m", 2);
	exit(1);
}

void	ft_error3(char *str)
{
	ft_putstr_fd("\033[33m", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(" is not a valid file\n", 2);
	ft_putstr_fd("\033[0m", 2);
	exit(1);
}

void	ft_error4(int nb_arg, char *op)
{
	ft_putstr_fd("\033[33m", 2);
	ft_putstr_fd("The parameter n°", 2);
	ft_putnbr_fd(nb_arg, 2);
	ft_putstr_fd(" is invalid for instruction ", 2);
	ft_putstr_fd(op, 2);
	ft_putstr_fd("\n", 2);
	ft_putstr_fd("\033[0m", 2);
	exit(1);
}

void	ft_error5(char *str)
{
	ft_putstr_fd("\033[33m", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("\033[0m", 2);
}
