/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artprevo <artprevo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/31 15:13:03 by artprevo          #+#    #+#             */
/*   Updated: 2020/08/02 12:57:26 by artprevo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

t_env		*init_env(void)
{
	t_env *env;

	if (!(env = (t_env *)malloc(sizeof(t_env))))
		ft_error2("Error on initial malloc\n");
	env->champion = NULL;
	env->action = NULL;
	env->champion_fetched = FALSE;
	env->prog_size = 0;
	env->nb_line = 1;
	env->line = NULL;
	env->token = 1;
	env->id_label = 0;
	return (env);
}

t_champion	*init_champion(t_env *env)
{
	t_champion *champion;

	if (!(champion = (t_champion *)malloc(sizeof(t_champion))))
		ft_error(env, "Error on champion malloc");
	champion->env = env;
	champion->fd = 0;
	champion->name = NULL;
	champion->comment = NULL;
	return (champion);
}

t_action	*init_action(t_env *env)
{
	t_action	*action;

	if (!(action = (t_action *)malloc(sizeof(t_action))))
		ft_error(env, "Error on action malloc");
	action->env = env;
	action->name = NULL;
	action->next = NULL;
	action->prev = NULL;
	action->op = NULL;
	action->id_label = 0;
	return (action);
}

t_op		*init_op(void)
{
	t_op	*op;

	if (!(op = (t_op *)malloc(sizeof(t_op))))
		ft_error2("Error on op malloc\n");
	op->op = NULL;
	op->nb_arg = 0;
	op->opcode = 0;
	op->cycles = 0;
	op->des = NULL;
	op->ocp = 0;
	op->carry = 0;
	op->label_size = 0;
	op->op = 0;
	op->weight = 0;
	op->next = NULL;
	op->param = NULL;
	return (op);
}

t_param		*init_param(int op_type, t_env *env)
{
	t_param		*param;

	if (!(param = (t_param *)malloc(sizeof(t_param))))
		ft_error(env, "Error on param malloc");
	param->env = env;
	param->label = NULL;
	param->arg_type = 0;
	param->arg_value = 0;
	param->op_type = op_type;
	param->label_size = g_op_tab[op_type].label_size;
	param->prev = NULL;
	param->next = NULL;
	return (param);
}
