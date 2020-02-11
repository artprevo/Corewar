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

#include "asm.h"

static int			processparsing(t_env *env)
{
	char	*line;

	line = NULL;
	while (get_next_line(0, &line) == TRUE)
	{
		if (fetch_champ(env, line) == FAILURE)
			return (FAILURE);
		if (fetch_actions(env, line) == FAILURE)
			return (FAILURE);
		if (env->champion->comment)
			env->champion_fetched = TRUE;
		free(line);
	}
	return (SUCCESS);
}

int		main(void)
{
	t_env		*env;

	if (!(env = init_env()))
		ft_putstr("Error Malloc\n");
	if (env)
	{
		if (processparsing(env) == FAILURE)
			ft_putstr("Error Parsing\n");
		else
		{
			printf("name champ = %s\n", env->champion->name);
			printf("comment champ = %s\n", env->champion->comment);
			// print_action(env);
			print_op(env);
		}
	}
	return (0);
}
