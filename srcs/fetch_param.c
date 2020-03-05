#include "asm.h"

int				label_name(char *line, t_param *param, int i)
{
	int		len;
	int		j;
	char	*tmp;

	len = 0;
	j = 0;
	if (!(line[i]))
		return (FAILURE);
	while (line[i] && strchr(LABEL_CHARS, line[i]) != 0)
	{
		len++;
		i++;
	}
	if (!(tmp = ft_strnew(len + 1)))
		return (FAILURE);
	i = i - len;
	while (line[i] && strchr(LABEL_CHARS, line[i]) != 0)
		tmp[j++] = line[i++];
	tmp[j] = '\0';
	param->label = tmp;
	return (SUCCESS);
}

int				fill_reg(char *line, t_param *param, int j)
{
	char	*tmp;
	int		i;
	int		len;

	i = 0;
	len = 0;
	while (line[j] && line[j] != SEPARATOR_CHAR)
	{
		len++;
		j++;
	}
	if (param->arg_type == T_IND)
		len++;
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

static int		fill_param(char *line, t_op *op, int j, int i)
{
	t_param		*param;
	int			ret;

	param = op->param;
	while (line[++j] && line[j] != COMMENT_CHAR)
	{
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
			if (fetch_directchar(line, param, j) == FAILURE)
				return (FAILURE);
			param = param->next;
			i++;
		}
		if ((ret = fetch_indirect(line, param, j, &i)) == FAILURE)
			return (FAILURE);
		if (ret == TRUE)
			param = param->next;
	}
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

int				fetch_param(t_env *env, char *line, t_op *op, int op_type)
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
	if (fill_param(line, op, -1, 0) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}