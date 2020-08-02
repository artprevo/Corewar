/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fetch_label.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artprevo <artprevo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/31 15:12:20 by artprevo          #+#    #+#             */
/*   Updated: 2020/08/02 14:13:17 by artprevo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static void		action_name(t_action *action, char *line)
{
	int		i;
	int		j;
	int		len;
	char	*tmp;

	i = 0;
	j = 0;
	len = 0;
	while (line[i] != LABEL_CHAR)
		i++;
	i--;
	while (i >= 0 && ft_strchr(LABEL_CHARS, line[i]) != 0 && i >= 0)
	{
		i--;
		len++;
	}
	if (!(tmp = ft_strnew(len + 1)))
		ft_error(action->env, "Error on malloc for action name");
	while (line[++i] != LABEL_CHAR)
		tmp[j++] = line[i];
	tmp[j] = '\0';
	action->name = tmp;
}

int				is_label(char *line)
{
	int i;

	i = 0;
	while (line[i])
	{
		if (line[i] == LABEL_CHAR && i != 0)
		{
			if (ft_strchr(LABEL_CHARS, line[i - 1]) != 0)
				return (TRUE);
		}
		i++;
	}
	return (FALSE);
}

int				fetch_label(t_env *env, char *line)
{
	t_action	*action;

	if (is_label(line) == TRUE)
	{
		if (!(action = init_action(env)))
			ft_error(env, "Error on malloc for action");
		action_name(action, line);
		add_action(env, action);
		action->id_label = env->id_label++;
		env->token = DEFAULT;
	}
	return (SUCCESS);
}
