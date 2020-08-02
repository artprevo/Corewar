/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artprevo <artprevo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/31 15:13:24 by artprevo          #+#    #+#             */
/*   Updated: 2020/08/02 14:03:01 by artprevo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static int	value_process1(int id_label, t_op *c_op, t_op *op, int check)
{
	if (id_label == c_op->id_label)
		check += 1;
	else if (op->id_label == c_op->id_label)
		check += 2;
	return (check);
}

int			get_value(t_env *env, t_op *op, int id_label)
{
	int				check;
	int				value;
	t_action		*current_action;
	t_op			*current_op;

	current_action = env->action;
	check = 0;
	value = 0;
	while (current_action)
	{
		current_op = current_action->op;
		while (current_op)
		{
			check = value_process1(id_label, current_op, op, check);
			if (check == 3)
				return (value);
			if (check == 1)
				value -= current_op->weight;
			else if (check == 2)
				value += current_op->weight;
			current_op = current_op->next;
		}
		current_action = current_action->next;
	}
	return (value);
}

int			get_id_label(t_env *env, char *arg)
{
	int				id_label;
	t_action		*current_action;

	id_label = 0;
	current_action = env->action;
	while (current_action)
	{
		if (ft_strequ(current_action->name, arg))
		{
			id_label = current_action->op->id_label;
			return (id_label);
		}
		current_action = current_action->next;
	}
	ft_error2("Error, label not found\n");
	return (FAILURE);
}
