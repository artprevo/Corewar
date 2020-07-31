/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fetch_actions_op.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artprevo <artprevo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/31 15:11:42 by artprevo          #+#    #+#             */
/*   Updated: 2020/07/31 15:11:43 by artprevo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static int		op_dup(t_op *op, int op_type)
{
	if (!(op->op = ft_strdup(g_op_tab[op_type].op)))
		return (FAILURE);
	op->nb_arg = g_op_tab[op_type].nb_arg;
	op->opcode = g_op_tab[op_type].opcode;
	op->cycles = g_op_tab[op_type].cycles;
	if (!(op->des = ft_strdup(g_op_tab[op_type].des)))
		return (FAILURE);
	op->ocp = g_op_tab[op_type].ocp;
	op->carry = g_op_tab[op_type].carry;
	op->label_size = g_op_tab[op_type].label_size;
	op->next = NULL;
	return (SUCCESS);
}

void			clean_line(char *line)
{
	int i;

	if (is_label(line) == TRUE)
	{
		i = 0;
		while (line[i] != LABEL_CHAR)
			line[i++] = ' ';
		line[i] = ' ';
	}
	i = 0;
	while (line[i])
	{
		if (line[i] == COMMENT_CHAR)
		{
			while (line[i])
				line[i++] = ' ';
			break ;
		}
		i++;
	}
}

static int		find_op(char *line)
{
	int		i;
	int		j;
	char	*tmp;

	tmp = ft_strdup(line);
	j = 0;
	while (tmp[j])
	{
		if (tmp[j] == LABEL_CHAR)
		{
			while (tmp[j] && tmp[j] != SEPARATOR_CHAR)
			{
				tmp[j] = 'a';
				j++;
			}
			break ;
		}
		j++;
	}
	i = 15;
	while (i >= 0 && ft_strnstr(tmp, g_op_tab[i].op, ft_strlen(tmp)) == 0)
		i--;
	free(tmp);
	return (i);
}

int				fetch_op(t_env *env, char *line)
{
	int		i;
	t_op	*op;

	clean_line(line);
	i = 15;
	i = find_op(line);
	if (i >= 0)
	{
		if (!env->action || ft_strcmp(env->action->name, "pattern") == 0
		|| env->token == NEW_ACTION)
			fetch_label(env, "pattern:");
		if (!(op = init_op()))
			ft_error(env, "Malloc error on OPs creation");
		if (op_dup(op, i) == FAILURE)
			ft_error(env, "Malloc error on OPs duplication");
		add_op(env->action, op);
		if (fetch_param(env, line, op, i) == FAILURE)
			ft_error(env, "Error on parameter fetch");
	}
	return (SUCCESS);
}

int				fetch_actions(t_env *env, char *line)
{
	if (env->champion_fetched == TRUE)
	{
		if (not_allowed(line) == TRUE)
			ft_error(env, "Wrong syntax");
		if (line[0] == '.')
			ft_error(env, "Wrong syntax");
		if (line_empty(env, line) == TRUE)
			env->token = NEW_ACTION;
		if (fetch_label(env, line) == FAILURE)
			ft_error(env, "Error on label fetch");
		if (fetch_op(env, line) == FAILURE)
			ft_error(env, "Error on op fetch");
	}
	return (SUCCESS);
}
