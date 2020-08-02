/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artprevo <artprevo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/13 17:29:39 by artprevo          #+#    #+#             */
/*   Updated: 2020/08/02 15:06:21 by artprevo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

t_op	g_op_tab[17] =
{
	{"live", 1, {T_DIR}, 1, 10, "alive", 0, 0, 4, 0, 0, NULL, NULL},
	{"ld", 2, {T_DIR | T_IND, T_REG}, 2, 5, "load", 1, 1, 4, 0, 0, NULL, NULL},
	{"st", 2, {T_REG, T_IND | T_REG}, 3, 5, "store", 1, 1, 0, 0, 0, NULL, NULL},
	{"add", 3, {T_REG, T_REG, T_REG}, 4, 10, "addition", 1, 1, 0, 0, 0,
		NULL, NULL},
	{"sub", 3, {T_REG, T_REG, T_REG}, 5, 10, "soustraction", 1, 1, 0, 0, 0,
		NULL, NULL},
	{"and", 3, {T_REG | T_DIR | T_IND, T_REG | T_IND | T_DIR, T_REG}, 6, 6,
		"et (and  r1, r2, r3   r1&r2 -> r3", 1, 1, 4, 0, 0, NULL, NULL},
	{"or", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 7, 6,
		"ou  (or   r1, r2, r3   r1 | r2 -> r3", 1, 1, 4, 0, 0, NULL, NULL},
	{"xor", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 8, 6,
		"ou (xor  r1, r2, r3   r1^r2 -> r3", 1, 1, 4, 0, 0, NULL, NULL},
	{"zjmp", 1, {T_DIR}, 9, 20, "jump if zero", 0, 0, 2, 0, 0, NULL, NULL},
	{"ldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 10, 25,
		"load index", 1, 0, 2, 0, 0, NULL, NULL},
	{"sti", 3, {T_REG, T_REG | T_DIR | T_IND, T_DIR | T_REG}, 11, 25,
		"store index", 1, 0, 2, 0, 0, NULL, NULL},
	{"fork", 1, {T_DIR}, 12, 800, "fork", 0, 0, 2, 0, 0, NULL, NULL},
	{"lld", 2, {T_DIR | T_IND, T_REG}, 13, 10, "long load", 1, 1, 4, 0, 0,
		NULL, NULL},
	{"lldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 14, 50,
		"long load index", 1, 1, 2, 0, 0, NULL, NULL},
	{"lfork", 1, {T_DIR}, 15, 1000, "long fork", 0, 0, 2, 0, 0, NULL, NULL},
	{"aff", 1, {T_REG}, 16, 2, "aff", 1, 0, 0, 0, 0, NULL, NULL},
	{0, 0, {0}, 0, 0, 0, 0, 0, 0, 0, 0, NULL, NULL}
};

static void			process_calcul(t_env *env)
{
	t_action	*action;

	if (env->action)
	{
		action = env->action;
		while (action->prev)
			action = action->prev;
		env->action = action;
		good_args(env, 0);
		process_ocp(env);
		weight_and_size(env);
		empty_action(env);
		id_op(env);
	}
}

static int			processparsing(t_env *env)
{
	char	*line;
	int		ctrl;

	line = NULL;
	while ((ctrl = get_next_line2(env->champion->fd, &line, 0)) != 0)
	{
		if (ctrl == -1)
			return (FAILURE);
		if (line && (env->line = line))
		{
			if (fetch_champ(env, line) == FAILURE)
				return (FAILURE);
			if (fetch_actions(env, line) == FAILURE)
				return (FAILURE);
			if (env->champion->name && env->champion->comment)
				env->champion_fetched = TRUE;
			env->nb_line++;
			if (full_empty(line, 0, 0, 0) == TRUE)
				ft_error(env, "Wrong syntax");
			free(line);
		}
	}
	if (env->champion_fetched == FALSE)
		no_champion(env);
	return (SUCCESS);
}

static int			processing(t_env *env, char *file)
{
	t_champion		*champ;

	champ = init_champion(env);
	env->champion = champ;
	if ((champ->fd = open(file, O_RDONLY)) == -1)
		ft_error(env, "Wrong champion file on input");
	if (processparsing(env) == FAILURE)
		ft_error(env, "Parsing failed");
	if (close(champ->fd) == -1)
		ft_error(env, "Error on closing champion file");
	if ((champ->fd = open(env->file_name, O_CREAT |
		O_WRONLY | O_TRUNC, S_IRUSR | S_IWUSR)) == -1)
		ft_error(env, "Error on creating the .cor file");
	process_calcul(env);
	write_header(env);
	write_champ(env, 0, env->action);
	if (close(champ->fd) == -1)
		ft_error(env, "Error on closing the new file");
	return (SUCCESS);
}

int					main(int ac, char **av)
{
	t_env		*env;
	int			i;

	if (ac <= 1)
		ft_error2("usage: ./asm champion1.s champion2.s ...\n");
	i = 1;
	while (av[i])
	{
		if (!illgal_file(av[i]))
		{
			env = init_env();
			if (env)
			{
				env->file_name = ft_strjoinf_l(file_name(av[i]), ".cor");
				processing(env, av[i]);
				writing_output(env->file_name);
				tafreetatoucompris(env);
			}
		}
		else
			ft_error3(av[i]);
		i++;
	}
	return (0);
}
