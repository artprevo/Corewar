/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artprevo <artprevo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/31 15:13:09 by artprevo          #+#    #+#             */
/*   Updated: 2020/07/31 18:15:21 by artprevo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int				not_allowed(char *line)
{
	int	i;
	int comment;

	comment = FALSE;
	i = 0;
	while (line[i])
	{
		if (line[i] == COMMENT_CHAR)
			comment = TRUE;
		if (strchr(LABEL_CHARS, line[i]) == 0 && line[i] != '\n' && line[i] != 9
		&& strchr(ALLOWED_CHARS, line[i]) == 0)
		{
			if (comment == FALSE)
				return (TRUE);
		}
		i++;
	}
	return (FALSE);
}

void			no_champion(t_env *env)
{
	if (!env->champion->name)
	{
		ft_error2("A champion has no name, we named him Jaqen H'ghar\n");
		env->champion->name = ft_strdup("Jaqen H'ghar");
	}
	if (!env->champion->comment)
	{
		ft_error2("A champion has no description, but it's not important\n");
		env->champion->comment = ft_strdup("Valar morghulis");
	}
}

static int		arg_type_tool(t_param *param, int arg_type)
{
	if (param->arg_type == T_LAB)
		arg_type = T_DIR;
	else
		arg_type = param->arg_type;
	return (arg_type);
}

void			good_args(t_env *env, int i)
{
	int			arg_type;
	t_action	*action;
	t_op		*op;
	t_param		*param;

	action = env->action;
	while (action)
	{
		op = action->op;
		while (op)
		{
			i = 0;
			param = op->param;
			while (param)
			{
				arg_type = arg_type_tool(param, arg_type);
				if (!(arg_type & g_op_tab[param->op_type].args[i++]))
					ft_error4(i - 1, op->op);
				param = param->next;
			}
			op = op->next;
		}
		action = action->next;
	}
}
