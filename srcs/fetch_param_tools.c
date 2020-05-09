#include "asm.h"

int			fetch_directchar(char *line, t_param *param, int j)
{
	if (line[j + 1] && line[j + 1] == LABEL_CHAR)
	{
		// printf("line dans fetch = %s\n", line);
		param->arg_type = T_LAB;
		if (label_name(line, param, j + 2) == FAILURE)
			ft_error(param->env, "Error on label name extraction");
	}
	else
	{
		param->arg_type = T_DIR;
		if (fill_reg(line, param, j) == FAILURE)
			ft_error(param->env, "Error on register malloc");
	}
	return (SUCCESS);
}

int			fetch_indirect(char *line, t_param *param, int j, int *i)
{
	if (!line[j] || !param)
		return (SUCCESS);
	if (line[j] == LABEL_CHAR && line[j - 1] != DIRECT_CHAR)
	{
		param->arg_type = T_IND;
		if (!(param->arg_type & g_op_tab[param->op_type].args[*i]))
		 	ft_error(param->env, "Error, wrong argument for this op");
		if (label_name(line, param, j + 1) == FAILURE)
			ft_error(param->env, "Error on label name extraction");
		*i += 1;
		return (TRUE);
	}
	if (line[j] == ',' || (line[j] == ' ' && param->prev == NULL))
	{
		// printf("on est ici\nline = %s\nline[j] = %c\n", line, line[j]);
		while (line[j])
		{
			if (line[j] == 'r' || line[j] == DIRECT_CHAR || line[j] == LABEL_CHAR)
				return (SUCCESS);
			if (ft_isdigit(line[j]) == 1)
			{
				j--;
				break ;
			}
			j++;
		}
		param->arg_type = T_IND;
		if (!(param->arg_type & g_op_tab[param->op_type].args[*i]))
		 	ft_error(param->env, "Error, wrong argument for this op");
		if (fill_reg(line, param, j + 1) == FAILURE)
			ft_error(param->env, "Error on register malloc");
		*i += 1;
		return (TRUE);
	}
	return (SUCCESS);
}
