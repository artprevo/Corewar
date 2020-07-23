#include "asm.h"

int		get_value(t_env *env, t_op *op, int id_label)
{
	int				check;
	int				value;
	t_action		*current_action;
	t_op			*current_op;

	current_action = env->action;
	check = 0;
	value = 0;
	// printf("\n\n");
	while (current_action)
	{
		current_op = current_action->op;
		while (current_op)
		{
			// printf("\033[1;36maction = %s\033[0m\n", current_action->name);
			// printf("\033[1;33mcheck before = %d\033[0m\n", check);
			// printf("\033[0;32mlabel recu = %d || action recue = %s\n\033[0m", id_label, action->name);
			// printf("value dans getvalue = %d\n", value);
			// printf("id_label = %d || weight = %d\n", op->id_label, op->weight);
			if (id_label == current_op->id_label)
				check += 1;
			else if (op->id_label == current_op->id_label)
				check += 2;
			if (check == 3)
				return (value);
			if (check == 1)
				value -= current_op->weight;
			else if (check == 2)
				value += current_op->weight;
			current_op = current_op->next;
			// printf("\033[1;33mcheck after = %d\033[0m\n", check);
		}
		current_action = current_action->next;
	}
	if (value == 0)
		ft_error(env, "Error, wrong label");
	return (value);
}

int		get_id_label(t_env *env, t_op *op, char *arg)
{
	int				id_label;
	t_action		*current_action;

	id_label = 0;
	current_action = env->action;
	// printf("label recherché = %s\n", arg);
	while (current_action)
	{
		if (ft_strequ(current_action->name, arg))
		{
			id_label = current_action->op->id_label;
			// printf("label trouvé = %s || son id = %d\n", current_action->name, id_label);
			return (id_label);
		}
		current_action = current_action->next;
	}
	ft_error(env, "Error, label not found");
}
