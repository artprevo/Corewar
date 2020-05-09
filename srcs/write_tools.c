#include "asm.h"

int		get_value(t_action *action, int id_label)
{
	int				value;
	t_action		*current_action;
	int				check;

	current_action = action->env->action;
	check = 0;
	value = 0;
	while (current_action)
	{
		// printf("action = %s || weight = %d\n", current_action->name, current_action->weight);
		if (id_label == current_action->id_label)
			check += 1;
		else if (action->id_label == current_action->id_label)
			check += 2;
		if (check == 3)
			return (value);
		if (check == 1)
			value -= current_action->weight;
		else if (check == 2)
			value += current_action->weight;
		current_action = current_action->next;
	}
	if (value == 0)
		ft_error(action->env, "Error, wrong label");
	return (value);
}

int		get_id_label(t_action *action, char *arg)
{
	int				id_label;
	t_env			*env;
	t_action		*current_action;

	id_label = 0;
	env = action->env;
	current_action = env->action;
	while (current_action)
	{
		if (ft_strequ(current_action->name, arg))
		{
			id_label = current_action->id_label;
			return (id_label);
		}
		current_action = current_action->next;
	}
	return (id_label);
}
