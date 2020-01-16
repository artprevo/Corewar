/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artprevo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/13 17:29:39 by artprevo          #+#    #+#             */
/*   Updated: 2020/01/13 17:39:37 by artprevo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static int			processparsing(t_env *env)
{
	char	*line;

	line = NULL;
	while (get_next_line(0, &line) == TRUE)
	{
		if (get_op(env, line) == FAILURE)
			return (FAILURE);
		free(line);
	}
	return (SUCCESS);
}

int		main(int ac, char **av)
{
	int a = ac;
	processparsing(env);
	return (0);
}
