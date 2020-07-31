/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   weight_and_size.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artprevo <artprevo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/31 15:13:13 by artprevo          #+#    #+#             */
/*   Updated: 2020/07/31 15:13:13 by artprevo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static void	update_weight(t_env *env, t_op *op, int add)
{
	env->prog_size += add;
	op->weight += add;
}

static void	weight_calcul(t_env *env, t_param *param, t_op *op)
{
	if (param->arg_type == T_REG)
		update_weight(env, op, 1);
	if (param->arg_type == T_DIR || param->arg_type == T_LAB)
		update_weight(env, op, op->label_size);
	if (param->arg_type == T_IND)
		update_weight(env, op, 2);
}

void		weight_and_size(t_env *env)
{
	t_action	*action;
	t_op		*op;
	t_param		*param;

	action = env->action;
	while (action)
	{
		op = action->op;
		while (op)
		{
			update_weight(env, op, (op->ocp) ? 2 : 1);
			param = op->param;
			while (param)
			{
				weight_calcul(env, param, op);
				param = param->next;
			}
			op = op->next;
		}
		action = action->next;
	}
}
