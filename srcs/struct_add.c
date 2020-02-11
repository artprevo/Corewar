#include "asm.h"

void			add_action(t_env *env, t_action *action)
{
	t_action	*tmp;

	if (env->action == NULL)
		env->action = action;
	else
	{
		tmp = env->action;
		while (tmp->next)
			tmp = tmp->next;
		action->prev = tmp;
		tmp->next = action;
		env->action = action;
	}
}

void			add_op(t_action *action, t_op *op)
{
	t_op	*tmp;

	if (action->op == NULL)
		action->op = op;
	else
	{
		tmp = action->op;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = op;
	}
}

void			add_param(t_op *op, t_param *param)
{
	t_param	*tmp;

	if (op->param == NULL)
		op->param = param;
	else
	{
		tmp = op->param;
		while (tmp->next)
			tmp = tmp->next;
		param->prev = tmp;
		tmp->next = param;
	}
}
