#include "asm.h"

t_op	g_op_tab[17] =
{
	{"live", 1, {T_DIR}, 1, 10, "alive", 0, 0, 4, NULL, NULL},
	{"ld", 2, {T_DIR | T_IND, T_REG}, 2, 5, "load", 1, 1, 4, NULL, NULL},
	{"st", 2, {T_REG, T_IND | T_REG}, 3, 5, "store", 1, 1, 0, NULL, NULL},
	{"add", 3, {T_REG, T_REG, T_REG}, 4, 10, "addition", 1, 1, 0, NULL, NULL},
	{"sub", 3, {T_REG, T_REG, T_REG}, 5, 10, "soustraction", 1, 1, 0, NULL, NULL},
	{"and", 3, {T_REG | T_DIR | T_IND, T_REG | T_IND | T_DIR, T_REG}, 6, 6,
		"et (and  r1, r2, r3   r1&r2 -> r3", 1, 1, 4, NULL, NULL},
	{"or", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 7, 6,
		"ou  (or   r1, r2, r3   r1 | r2 -> r3", 1, 1, 4, NULL, NULL},
	{"xor", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 8, 6,
		"ou (xor  r1, r2, r3   r1^r2 -> r3", 1, 1, 4, NULL, NULL},
	{"zjmp", 1, {T_DIR}, 9, 20, "jump if zero", 0, 0, 2, NULL, NULL},
	{"ldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 10, 25,
		"load index", 1, 0, 2, NULL, NULL},
	{"sti", 3, {T_REG, T_REG | T_DIR | T_IND, T_DIR | T_REG}, 11, 25,
		"store index", 1, 0, 2, NULL, NULL},
	{"fork", 1, {T_DIR}, 12, 800, "fork", 0, 0, 2, NULL, NULL},
	{"lld", 2, {T_DIR | T_IND, T_REG}, 13, 10, "long load", 1, 1, 4, NULL, NULL},
	{"lldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 14, 50,
		"long load index", 1, 1, 2, NULL, NULL},
	{"lfork", 1, {T_DIR}, 15, 1000, "long fork", 0, 0, 2, NULL, NULL},
	{"aff", 1, {T_REG}, 16, 2, "aff", 1, 0, 0, NULL, NULL},
	{0, 0, {0}, 0, 0, 0, 0, 0, 0, NULL, NULL}
};

static int		fill_reg(char *line, t_param *param, int j)
{
	char	*tmp;
	int		i;
	int		len;

	i = 0;
	len = 0;
	while (line[j] != SEPARATOR_CHAR && line[j])
	{
		len++;
		j++;
	}
	if (!(tmp = ft_strnew(len)))
		return (FAILURE);
	j = j - len + 1;
	while (line[j] && line[j] != SEPARATOR_CHAR)
			tmp[i++] = line[j++];
	tmp[i] = '\0';
	param->arg_value = ft_atoi(tmp);
	free(tmp);
	return (SUCCESS);
}

static int		fill_param(char *line, t_op *op, int op_type)
{
	t_param		*param;
	int			i;
	int			j;

	i = 0;
	j = 0;
	op_type = 0;
	param = op->param;
	while (line[j])
	{
		if (line[j] == COMMENT_CHAR)
			break ;
		if (line[j] == 'r' && ft_isalnum(line[j - 1]) == 0 && (ft_isdigit(line[j + 1]) == 1))
		{
			param->arg_type = T_REG;
			if (fill_reg(line, param, j) == FAILURE)
				return (FAILURE);
			param = param->next;
			i++;
		}
		else if (line[j] == DIRECT_CHAR)
		{
			if (line[j + 1] && line[j + 1] == LABEL_CHAR)
			{
				param->arg_type = T_LAB;
				if (label_name(line, param, j + 2) == FAILURE)
					return (FAILURE);
			}
			else
			{
				param->arg_type = T_DIR;
				if (fill_reg(line, param, j) == FAILURE)
					return (FAILURE);
			}
			param = param->next;
			i++;
		}
		j++;
	}
	printf("i = %d\n", i);
	if (i != op->nb_arg)
		return (FAILURE);
	return (SUCCESS);
}

static int		make_param(t_op *op, int nb_arg)
{
	t_param		*param;
	int			i;

	i = 0;
	while (i < nb_arg)
	{
		if (!(param = init_param()))
			return (FAILURE);
		else
			add_param(op, param);
		i++;
	}
	return (SUCCESS);
}

static int		fetch_param(t_env *env, char *line, t_op *op, int op_type)
{
	int	i;
	int	separator;

	i = 0;
	separator = 0;
	while (line[i])
	{
		if (line[i] == SEPARATOR_CHAR)
			separator++;
		i++;
	}
	if ((separator + 1) != op->nb_arg)
		return (FAILURE);
	if (make_param(op, g_op_tab[op_type].nb_arg) == FAILURE)
		return (FAILURE);
	if (fill_param(line, op, op_type) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}

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
		printf("action->name = %s\n", env->action->name);
		add_op(env->action, op);
		printf("name = %s\n", op->op);
		if (fetch_param(env, line, op, i) == FAILURE)
			return (FAILURE);
	}
	return (SUCCESS);
}
