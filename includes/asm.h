/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artprevo <artprevo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/31 15:26:11 by artprevo          #+#    #+#             */
/*   Updated: 2020/08/02 16:44:23 by artprevo         ###   ########.fr       */
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

# define DEFAULT		1
# define NEW_ACTION		2

extern t_op				g_op_tab[17];

typedef struct			s_env
{
	struct s_champion	*champion;
	struct s_action		*action;
	int					champion_fetched;
	int					prog_size;
	int					nb_line;
	char				*line;
	int					token;
	int					id_label;
	char				*file_name;
}						t_env;

typedef struct			s_action
{
	t_env				*env;
	char				*name;
	int					id_label;
	struct s_op			*op;
	struct s_action		*next;
	struct s_action		*prev;
}						t_action;

typedef struct			s_champion
{
	t_env				*env;
	int					fd;
	char				*name;
	char				*comment;
}						t_champion;

typedef struct			s_param
{
	t_env				*env;
	char				*label;
	int					arg_type;
	int					arg_value;
	int					op_type;
	int					label_size;
	struct s_param		*prev;
	struct s_param		*next;
}						t_param;

int						fetch_champ(t_env *env, char *line);

int						fetch_actions(t_env *env, char *line);

int						fetch_label(t_env *env, char *line);
int						is_label(char *line);

int						fetch_param(t_env *env, char *line, t_op *op,
						int op_type);
int						fill_reg(char *line, t_param *param, int j);
int						label_name(char *line, t_param *param, int i);

int						fetch_indirect(char *line, t_param *param, int j,
						int *i);
int						fetch_directchar(char *line, t_param *param, int j);
void					param_reg(t_param *param, int i, int j, char *line);

int						fetch_op(t_env *env, char *line);

void					process_ocp(t_env *env);

t_env					*init_env();
t_champion				*init_champion(t_env *env);
t_action				*init_action(t_env *env);
t_op					*init_op(void);
t_param					*init_param(int op_type, t_env *env);

void					add_action(t_env *env, t_action *action);
void					add_op(t_action *action, t_op *op);
void					add_param(t_op *op, t_param *param);

void					write_header(t_env *env);

void					write_champ(t_env *env, int i, t_action *action);

void					ft_error(t_env *env, char *str);
void					ft_error2(char *str);
void					ft_error3(char *str);
void					ft_error4(int nb_arg, char *op);
void					ft_error5(char *str);
void					writing_output(char *str);

int						get_id_label(t_env *env, char *arg);
int						get_value(t_env *env, t_op *op, int id_label);

void					weight_and_size(t_env *env);

char					*file_name(char *str);
int						line_empty(t_env *env, char *line);
void					empty_action(t_env *env);
void					id_op(t_env *env);
int						illgal_file(char *s);
void					tafreetatoucompris(t_env *env);
int						get_next_line2(const int fd, char **line, int rd);

int						not_allowed(char *line);
void					no_champion(t_env *env);
void					good_args(t_env *env, int i);
int						full_empty(char *line, int ret, int isok, int isnotok);

#endif
