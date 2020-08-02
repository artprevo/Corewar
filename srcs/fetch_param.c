/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fetch_param.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artprevo <artprevo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/31 15:12:23 by artprevo          #+#    #+#             */
/*   Updated: 2020/08/02 16:45:23 by artprevo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	if (j > (int)ft_strlen(line))
		ft_error(param->env, "Wrong syntax");
	while (line[j] && line[j] != SEPARATOR_CHAR && j++)
		len++;
	if (param->arg_type == T_IND)
		len++;
	if (!(tmp = ft_strnew(len)))
		ft_error(param->env, "Error on register malloc");
	j = j - len + 1;
	if (param->arg_type == T_IND && line[j - 1] == '-')
		j--;
	while (line[j] && line[j] != SEPARATOR_CHAR)
		tmp[i++] = line[j++];
	tmp[i] = '\0';
	param->arg_value = ft_atoi(tmp);
	free(tmp);
	return (SUCCESS);
}

static void		fill_param(char *line, t_op *op, int j, int i)
{
	t_param		*param;
	int			ret;

	param = op->param;
	while (line[++j] && line[j] != COMMENT_CHAR)
	{
		if (line[j] == 'r' && ft_isalnum(line[j - 1]) == 0 &&
		(ft_isdigit(line[j + 1]) == 1))
		{
			param_reg(param, i, j, line);
			param = param->next;
			i++;
		}
		else if (line[j] == DIRECT_CHAR)
		{
			if (fetch_directchar(line, param, j) == FAILURE)
				ft_error(param->env, "Error on parameter fetch");
			param = param->next;
			i++;
		}
		if ((ret = fetch_indirect(line, param, j, &i)) == FAILURE)
			ft_error(param->env, "Error on parameter fetch");
		if (ret == TRUE)
			param = param->next;
	}
}

static int		make_param(t_env *env, t_op *op, int nb_arg, int op_type)
{
	t_param		*param;
	int			i;

	i = 0;
	while (i < nb_arg)
	{
		if (!(param = init_param(op_type, env)))
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
	if (separator + 1 != g_op_tab[op_type].nb_arg)
		ft_error(env, "Not the right numbers of arg for this op");
	if (make_param(env, op, g_op_tab[op_type].nb_arg, op_type) == FAILURE)
		ft_error(env, "Error on malloc");
	fill_param(line, op, -1, 0);
	return (SUCCESS);
}
