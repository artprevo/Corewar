#include "asm.h"

static void	update_weight(t_env *env, t_op *op, int add)
{
	env->prog_size += add;
	op->weight += add;
}

void	weight_and_size(t_env *env)
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
				if (param->arg_type == T_REG)
					update_weight(env, op, 1);
				if (param->arg_type == T_DIR || param->arg_type == T_LAB)
					update_weight(env, op, op->label_size);
				if (param->arg_type == T_IND)
					update_weight(env, op, 2);
				param = param->next;
			}
			op = op->next;
		}
		action = action->next;
	}
}
