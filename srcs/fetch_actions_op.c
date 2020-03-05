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

void 			clean_line(char *line)
{
	int i;

	if (is_label(line) == TRUE)
	{
		i = 0;
		while (line[i] != LABEL_CHAR)
		{
			line[i] = 'a';
			i++;
		}
	}
	i = 0;
	while (line[i])
	{
		if (line[i] == COMMENT_CHAR)
		{
			while (line[i])
			{
				line[i] = ' ';
				i++;
			}
			break ;
		}
		i++;
	}
}

int				fetch_op(t_env *env, char *line)
{
	int		i;
	t_op	*op;

	clean_line(line);
	i = 15;
	while (i >= 0 && ft_strnstr(line, g_op_tab[i].op, ft_strlen(line)) == 0)
		i--;
	if (i >= 0)
	{
		if (!(op = init_op()))
			return (FAILURE);
		if (op_dup(op, i) == FAILURE)
			return (FAILURE);
		add_op(env->action, op);
		if (fetch_param(env, line, op, i) == FAILURE)
			return (FAILURE);
	}
	return (SUCCESS);
}

int				fetch_actions(t_env *env, char *line)
{
	if (env->champion_fetched == TRUE)
	{
		if (fetch_label(env, line) == FAILURE)
			return (FAILURE);
		if (fetch_op(env, line) == FAILURE)
			return (FAILURE);
	}
	return (SUCCESS);
}
