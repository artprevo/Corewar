#include "asm.h"

void 	print_action(t_env *env)
{
	t_action	*action;

	action = env->action;
	while (action)
	{
		printf("action->name = %s\n", action->name);
		action = action->next;
	}
}

void 	print_param(t_op *op)
{
	t_param *param;
	int i = 0;

	param = op->param;
	while (param)
	{
		printf("PARAMETRE %d\n", i++);
		printf("label = %s\n", param->label);
		printf("arg_type = %d\n", param->arg_type);
		printf("arg_value = %d\n", param->arg_value);
		printf("\n");
		param = param->next;
	}
}
void 	print_op(t_env *env)
{
	t_op		*op;
	t_action	*action;

	printf("\n");

	action = env->action;
	while (action->prev)
		action = action->prev;
	while (action)
	{
		printf("action->name = %s\n", action->name);
		op = action->op;
		while (op)
		{
			printf("op = %s\n", op->op);
			printf("nb_arg = %d\n", op->nb_arg);
			printf("opcode = %d\n", op->opcode);
			printf("cycles = %d\n", op->cycles);
			printf("des = %s\n", op->des);
			printf("ocp = %d\n", op->ocp);
			printf("carry = %d\n", op->carry);
			printf("label_size = %d\n", op->label_size);
			printf("\n");
			print_param(op);
			op = op->next;
		}
		action = action->next;
	}
}
