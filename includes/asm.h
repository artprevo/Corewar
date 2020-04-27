/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h 	                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artprevo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/13 17:28:39 by artprevo          #+#    #+#             */
/*   Updated: 2020/01/13 17:28:40 by artprevo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H

# include "libft.h"
# include "op.h"

# define BUFFER_SIZE	10000
# define SHIFT_MIN		32
# define TRUE			1
# define FALSE 			0
# define SUCCESS 		0
# define FAILURE 		-1

extern t_op				g_op_tab[17];

typedef struct			s_env
{
	struct s_champion	*champion;
	struct s_action		*action;
	int					champion_fetched;
	int					prog_size;
}						t_env;

typedef struct			s_action
{
	char				*name;
	int					weight;
	struct s_op			*op;
	struct s_action		*next;
	struct s_action		*prev;
}						t_action;

typedef struct			s_champion
{
	int					fd;
	char				*name;
	char				*comment;
}						t_champion;

typedef struct			s_param
{
	char				*label;
	int					arg_type;
	int					arg_value;
	struct s_param		*prev;
	struct s_param		*next;
}						t_param;

// fetch_champ.c
int						fetch_champ(t_env *env, char *line);

// fetch_actions.c
int						fetch_actions(t_env *env, char *line);

// fetch_label.c
int						fetch_label(t_env *env, char *line);
int						is_label(char *line);

// fetch_param.c
int						fetch_param(t_env *env, char *line, t_op *op, int op_type);
int						fill_reg(char *line, t_param *param, int j);
int						label_name(char *line, t_param *param, int i);

// fetch_param_tools.c
int						fetch_indirect(char *line, t_param *param, int j, int *i);
int						fetch_directchar(char *line, t_param *param, int j);

// fetch_op.c
int						fetch_op(t_env *env, char *line);

// process_ocp.cs
int						process_ocp(t_env *env);

// struct_init.c
t_env					*init_env(void);
t_champion				*init_champion(void);
t_action				*init_action(void);
t_op					*init_op(void);
t_param					*init_param(void);

// struct_add.c
void					add_action(t_env *env, t_action *action);
void					add_op(t_action *action, t_op *op);
void					add_param(t_op *op, t_param *param);

// print.c
void 					print_action(t_env *env);
void 					print_op(t_env *env);

// write_header.c
int						write_header(t_env *env);

#endif
