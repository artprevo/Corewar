/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fetch_param_tools.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artprevo <artprevo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/31 15:12:26 by artprevo          #+#    #+#             */
/*   Updated: 2020/08/02 14:22:53 by artprevo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static void		fetch_indirect_param(t_param *param, char *line, int j)
{
	param->arg_type = T_IND;
	if (label_name(line, param, j + 1) == FAILURE)
		ft_error(param->env, "Error on label name extraction");
}

static void		fetch_error(t_param *param, int j, char *line)
{
	param->arg_type = T_IND;
	if (fill_reg(line, param, j + 1) == FAILURE)
		ft_error(param->env, "Wrong syntax");
}

int				fetch_directchar(char *line, t_param *param, int j)
{
	if (line[j + 1] && line[j + 1] == LABEL_CHAR)
	{
		param->arg_type = T_LAB;
		if (label_name(line, param, j + 2) == FAILURE)
			ft_error(param->env, "Error on label name extraction");
	}
	else
	{
		param->arg_type = T_DIR;
		if (fill_reg(line, param, j) == FAILURE)
			ft_error(param->env, "Wrong syntax");
	}
	return (SUCCESS);
}

int				fetch_indirect(char *line, t_param *param, int j, int *i)
{
	if (!line[j] || !param)
		return (SUCCESS);
	if (line[j] == LABEL_CHAR && line[j - 1] != DIRECT_CHAR)
	{
		fetch_indirect_param(param, line, j);
		*i += 1;
		return (TRUE);
	}
	if (line[j] == ',' || (line[j] == ' ' && param->prev == NULL))
	{
		while (line[j] && ft_isdigit(line[j]) != 1)
		{
			if (line[j] == 'r' || line[j] == DIRECT_CHAR ||
			line[j] == LABEL_CHAR)
				return (SUCCESS);
			j++;
		}
		if (ft_isdigit(line[j]) == 1)
			j--;
		fetch_error(param, j, line);
		*i += 1;
		return (TRUE);
	}
	return (SUCCESS);
}

void			param_reg(t_param *param, int i, int j, char *line)
{
	param->arg_type = T_REG;
	if (!(param->arg_type & g_op_tab[param->op_type].args[i]) ||
	fill_reg(line, param, j) == FAILURE)
		ft_error(param->env, "Wrong syntax");
}
