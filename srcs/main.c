/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artprevo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/13 17:29:39 by artprevo          #+#    #+#             */
/*   Updated: 2020/01/13 17:39:37 by artprevo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

t_op	g_op_tab[17] =
{
	{"live", 1, {T_DIR}, 1, 10, "alive", 0, 0, 4, NULL, NULL},
	{"ld", 2, {T_DIR | T_IND, T_REG}, 2, 5, "load", 1, 1, 4, NULL, NULL},
	{"st", 2, {T_REG, T_IND | T_REG}, 3, 5, "store", 1, 1, 0, NULL, NULL},
	{"add", 3, {T_REG, T_REG, T_REG}, 4, 10, "addition", 1, 1, 0, NULL, NULL},
	{"sub", 3, {T_REG, T_REG, T_REG}, 5, 10, "soustraction", 1, 1, 0, NULL, NULL},
	{"and", 3, {T_REG | T_DIR | T_IND, T_REG | T_IND | T_DIR, T_REG}, 6, 6,
		"et (and  r1, r2, r3   r1&r2 -> r3", 1, 1, 4, NULL, NULL},
	{"or", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 7, 6,
		"ou  (or   r1, r2, r3   r1 | r2 -> r3", 1, 1, 4, NULL, NULL},
	{"xor", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 8, 6,
		"ou (xor  r1, r2, r3   r1^r2 -> r3", 1, 1, 4, NULL, NULL},
	{"zjmp", 1, {T_DIR}, 9, 20, "jump if zero", 0, 0, 2, NULL, NULL},
	{"ldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 10, 25,
		"load index", 1, 0, 2, NULL, NULL},
	{"sti", 3, {T_REG, T_REG | T_DIR | T_IND, T_DIR | T_REG}, 11, 25,
		"store index", 1, 0, 2, NULL, NULL},
	{"fork", 1, {T_DIR}, 12, 800, "fork", 0, 0, 2, NULL, NULL},
	{"lld", 2, {T_DIR | T_IND, T_REG}, 13, 10, "long load", 1, 1, 4, NULL, NULL},
	{"lldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 14, 50,
		"long load index", 1, 1, 2, NULL, NULL},
	{"lfork", 1, {T_DIR}, 15, 1000, "long fork", 0, 0, 2, NULL, NULL},
	{"aff", 1, {T_REG}, 16, 2, "aff", 1, 0, 0, NULL, NULL},
	{0, 0, {0}, 0, 0, 0, 0, 0, 0, NULL, NULL}
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
		process_ocp(env);
		weight_and_size(env);
	}
}

static int			processparsing(t_env *env)
{
	char	*line;

	line = NULL;
	while (get_next_line(env->champion->fd, &line) == TRUE)
	{
		env->line = line;
		if (fetch_champ(env, line) == FAILURE)
			return (FAILURE);
		if (fetch_actions(env, line) == FAILURE)
			return (FAILURE);
		if (env->champion->comment)
			env->champion_fetched = TRUE;
		env->nb_line++;
		free(line);
	}
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
	if ((champ->fd = open(ft_strdup(env->file_name), O_CREAT |
		O_WRONLY | O_TRUNC, S_IRUSR | S_IWUSR)) == -1)
		ft_error(env, "Error on creating the .cor file");
	process_calcul(env);
	write_header(env);
	write_champ(env);
	if (close(champ->fd) == -1)
		ft_error(env, "Error on closing the new file");
	return (SUCCESS);
}

int		main(int ac, char **av)
{
	t_env		*env;
	char		*name;

	if (ac != 2)
		ft_error(env, "usage: ./asm champion.s\n");
	if (!(env = init_env()))
		ft_putstr("Error on malloc\n");
	if (env)
	{
		env->file_name = ft_strjoinf_l(file_name(av[1]), ".cor");
		if (processing(env, av[1]) == FAILURE)
			ft_error(env, "Ui ca c mal passe.");
		ft_putstr_fd("\033[32m", 2);
		ft_putstr_fd("Writing output program to ", 2);
		ft_putstr_fd(env->file_name, 2);
		ft_putstr_fd("\n\033[0m", 2);
		// else
		// {
		// 	printf("env->prog_size = %d\n", env->prog_size);
		// 	print_action(env);
		// }
		// 	// printf("name champ = %s\n", env->champion->name);
		// 	// printf("comment champ = %s\n", env->champion->comment);
			// print_op(env);
		// }
	}
	return (0);
}
