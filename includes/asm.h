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

/*
fetch_champ.c
*/
int						fetch_champ(t_env *env, char *line);

/*
fetch_actions.c
*/
int						fetch_actions(t_env *env, char *line);

/*
fetch_label.c
*/
int						fetch_label(t_env *env, char *line);
int						is_label(char *line);

/*
fetch_param.c
*/
int						fetch_param(t_env *env, char *line, t_op *op,
						int op_type);
int						fill_reg(char *line, t_param *param, int j);
int						label_name(char *line, t_param *param, int i);

/*
	fetch_param_tools.c
*/
int						fetch_indirect(char *line, t_param *param, int j,
						int *i);
int						fetch_directchar(char *line, t_param *param, int j);
void					param_reg(t_param *param, int i, int j, char *line);

/*
	fetch_op.c
*/

int						fetch_op(t_env *env, char *line);

/*
process_ocp.c
*/

void					process_ocp(t_env *env);

/*
	struct_init.c
*/
t_env					*init_env();
t_champion				*init_champion(t_env *env);
t_action				*init_action(t_env *env);
t_op					*init_op(void);
t_param					*init_param(int op_type, t_env *env);

/*
struct_add.c
*/
void					add_action(t_env *env, t_action *action);
void					add_op(t_action *action, t_op *op);
void					add_param(t_op *op, t_param *param);

/*
print.c
*/
void					print_action(t_env *env);
void					print_op(t_env *env);

/*
write_header.c
*/
void					write_header(t_env *env);

/*
write_champ.c
*/
void					write_champ(t_env *env, int i, t_action *action);

/*
ft_error.c
*/
void					ft_error(t_env *env, char *str);

/*
write_tools.c
*/
int						get_id_label(t_env *env, t_op *op, char *arg);
int						get_value(t_env *env, t_op *op, int id_label);

/*
weight_and_size.c
*/
void					weight_and_size(t_env *env);

/*
tools.c
*/
char					*file_name(char *str);
int						line_empty(t_env *env, char *line);
void					empty_action(t_env *env);
void					id_op(t_env *env);
int						illgal_file(char *s);

#endif
