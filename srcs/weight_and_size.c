#include "asm.h"

static void	update_weight(t_env *env, t_action *action, int add)
{
	env->prog_size += add;
	action->weight += add;
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
			update_weight(env, action, (op->ocp) ? 2 : 1);
			param = op->param;
			while (param)
			{
				if (param->arg_type == T_REG)
					update_weight(env, action, 1);
				if (param->arg_type == T_DIR || param->arg_type == T_LAB)
					update_weight(env, action, op->label_size);
				if (param->arg_type == T_IND)
					update_weight(env, action, 2);
				param = param->next;
			}
			op = op->next;
		}
		action = action->next;
	}
}
