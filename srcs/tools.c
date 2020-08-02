/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artprevo <artprevo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/31 15:13:06 by artprevo          #+#    #+#             */
/*   Updated: 2020/08/02 12:51:22 by artprevo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

char	*file_name(char *str)
{
	int		i;
	int		j;
	int		k;
	char	*file_name;

	i = 0;
	j = 0;
	while (str[i])
		i++;
	i -= 2;
	k = i;
	while (k != 0 && str[k] != '/')
		k--;
	if (k != 0)
		k++;
	k = 0;
	if (!(file_name = malloc(sizeof(char) * ((i - k) + 1))))
		ft_error2("Error on malloc for file_name\n");
	i = i - k;
	while (j < i)
		file_name[j++] = str[k++];
	file_name[j] = '\0';
	return (file_name);
}

int		line_empty(t_env *env, char *line)
{
	int i;

	i = 0;
	if (env->action)
	{
		if (ft_strcmp(env->action->name, "pattern") == 0)
			return (FALSE);
	}
	while (line[i])
	{
		if (line[i] != ' ' && line[i] != '\n')
			return (FALSE);
		i++;
	}
	return (TRUE);
}

void	empty_action(t_env *env)
{
	t_action	*action;

	action = env->action;
	while (action)
	{
		if (!action->op)
			action->op = init_op();
		action = action->next;
	}
}

void	id_op(t_env *env)
{
	int			id;
	t_action	*action;
	t_op		*op;

	id = 0;
	action = env->action;
	while (action)
	{
		op = action->op;
		while (op)
		{
			op->id_label = id++;
			op = op->next;
		}
		action = action->next;
	}
}

int		illgal_file(char *s)
{
	int			len;

	if (!s)
		return (1);
	len = ft_strlen(s);
	if (len < 2)
		return (1);
	if (s[len - 1] == 's' && s[len - 2] == '.')
		return (0);
	else
		return (1);
}
