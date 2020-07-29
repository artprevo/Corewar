#include "asm.h"

static void		calcul_process(t_param *param, t_op *op, int add)
{
	if (param->arg_type == T_REG)
		add = REG_CODE;
	if (param->arg_type == T_DIR || param->arg_type == T_LAB)
		add = DIR_CODE;
	if (param->arg_type == T_IND)
		add = IND_CODE;
	op->ocp += add;
	op->ocp *= 4;
}

static int		ocp_calcul(t_op *op)
{
	t_param		*param;
	int			add;
	int			nb_param;

	param = op->param;
	nb_param = 0;
	if (op->ocp == 0)
		return (SUCCESS);
	else
		op->ocp = 0;
	while (param)
	{
		calcul_process(param, op, add);
		param = param->next;
		nb_param++;
	}
	while (nb_param != 3)
	{
		op->ocp *= 4;
		nb_param++;
	}
	return (SUCCESS);
}

void			process_ocp(t_env *env)
{
	t_action	*action;
	t_op		*op;

	action = env->action;
	while (action)
	{
		op = action->op;
		while (op)
		{
			ocp_calcul(op);
			op = op->next;
		}
		action = action->next;
	}
}
