#include "asm.h"

int			fetch_directchar(char *line, t_param *param, int j)
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
	return (SUCCESS);
}

int			fetch_indirect(char *line, t_param *param, int j, int *i)
{
	if (line[j] == ',' && *i == 0)
	{
		j--;
		param->arg_type = T_IND;
		while (ft_isdigit(line[j]) == 1)
			j--;
		if (fill_reg(line, param, j) == FAILURE)
			return (FAILURE);
		*i += 1;
		return (TRUE);
	}
	if (line[j] == ',')
	{
		while (line[j])
		{
			if (line[j] == 'r' || line[j] == DIRECT_CHAR)
				return (SUCCESS);
			if (ft_isdigit(line[j]) == 1)
			{
				j--;
				break ;
			}
			j++;
		}
		param->arg_type = T_IND;
		if (fill_reg(line, param, j + 1) == FAILURE)
			return (FAILURE);
		*i += 1;
		return (TRUE);
	}
	return (SUCCESS);
}
