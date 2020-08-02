/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_champ.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artprevo <artprevo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/31 15:13:17 by artprevo          #+#    #+#             */
/*   Updated: 2020/08/02 15:40:40 by artprevo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static void	write_value(char *prog, int value, int size)
{
	size = (size) ? size : 2;
	if (size == 4)
	{
		prog[3] = value & 0xff;
		prog[2] = (value >> 8) & 0xff;
		prog[1] = (value >> 16) & 0xff;
		prog[0] = (value >> 24) & 0xff;
	}
	else
	{
		prog[1] = value & 0xff;
		prog[0] = (value >> 8) & 0xff;
	}
}

static void	write_label(char *prog, t_op *op, t_param *param, int dir)
{
	int				value;
	int				id_label;
	char			*arg;

	arg = param->label;
	value = 0;
	id_label = get_id_label(op->param->env, arg);
	if (id_label != op->id_label)
	{
		value = get_value(op->param->env, op, id_label);
		if (value == 0)
			ft_error(param->env, "Error, wrong label");
	}
	if (dir && param->label_size == 4)
	{
		prog[3] = value & 0xff;
		prog[2] = (value >> 8) & 0xff;
		prog[1] = (value >> 16) & 0xff;
		prog[0] = (value >> 24) & 0xff;
	}
	else
	{
		prog[1] = value & 0xff;
		prog[0] = (value >> 8) & 0xff;
	}
}

static void	write_args(t_op *op, char *prog, int *i)
{
	t_param			*param;
	int				dir;

	param = op->param;
	while (param)
	{
		if (param->arg_type == T_REG)
			prog[(*i)++] = (param->arg_value);
		else
		{
			dir = (param->arg_type == T_DIR || param->arg_type == T_LAB) ?
			1 : 0;
			if (param->label != NULL)
				write_label(&(prog[*i]), op, param, dir);
			else
				write_value(&(prog[*i]), param->arg_value, op->label_size *
				dir);
			*i += (dir) ? op->label_size : 2;
		}
		param = param->next;
	}
}

void		write_champ(t_env *env, int i, t_action *action)
{
	t_op			*op;
	char			*prog;

	if (!(prog = ft_memalloc(env->prog_size + 1)))
		ft_error(env, "Error on malloc");
	while (action)
	{
		op = action->op;
		while (op)
		{
			if (op->op)
			{
				prog[i++] = op->opcode;
				if (op->ocp)
					prog[i++] = op->ocp;
				write_args(op, prog, &i);
			}
			op = op->next;
		}
		action = action->next;
	}
	lseek(env->champion->fd, 0x890, SEEK_SET);
	write(env->champion->fd, prog, env->prog_size);
	ft_strdel(&prog);
}
