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

static void	write_label(char *prog, t_action *action, t_param *param, int dir)
{
	int				value;
	int				id_label;
	char			*arg;

	arg = param->label;
	id_label = get_id_label(action, arg);
	value = get_value(action, id_label);
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

static void	write_args(t_action *action, t_op *op, char *prog, int *i)
{
	t_param			*param;
	int				j;
	int				dir;

	j = -1;
	param = op->param;
	while (param)
	{
		// printf("label = %s\n", param->label);
		// printf("arg_type = %d\n", param->arg_type);
		// printf("arg_value = %d\n", param->arg_value);
		if (param->arg_type == T_REG)
			prog[(*i)++] = (param->arg_value);
		else
		{
			dir = (param->arg_type == T_DIR || param->arg_type == T_LAB) ? 1 : 0;
			if (param->label != NULL)
				write_label(&(prog[*i]), action, param, dir);
			else
				write_value(&(prog[*i]), param->arg_value, op->label_size * dir);
			*i += (dir) ? op->label_size : 2;
		}
		param = param->next;
	}
}

void	write_champ(t_env *env)
{
	t_action		*action;
	t_op			*op;
	char			*prog;
	int				i;

	// printf("env->prog_size = %d\n", env->prog_size);
	if (!(prog = ft_memalloc(env->prog_size + 1)))
		ft_error(env, "Error on malloc");
	i = 0;
	action = env->action;
	while (action)
	{
		// printf("ACTION NAME = %s || ACTION WEIGHT = %d\n", action->name, action->weight);
		op = action->op;
		while (op)
		{
			// printf("OP = %s\n", op->op);
			prog[i++] = op->opcode;
			if (op->ocp)
				prog[i++] = op->ocp;
			write_args(action, op, prog, &i);
			op = op->next;
			// printf("UNE ACTION ECRITE\n");
		}
		action = action->next;
	}
	lseek(env->champion->fd, 0x890, SEEK_SET);
	write(env->champion->fd, prog, env->prog_size);
	// printf("PROG WRITED\n");
	ft_strdel(&prog);
}
