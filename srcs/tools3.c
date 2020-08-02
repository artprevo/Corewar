/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artprevo <artprevo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/31 15:13:06 by artprevo          #+#    #+#             */
/*   Updated: 2020/08/02 16:44:16 by artprevo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		full_empty(char *line, int ret, int isok, int isnotok)
{
	int	i;

	i = 15;
	if (ft_strnstr(line, COMMENT_CMD_STRING, ft_strlen(line)) != 0)
		ret++;
	if (ft_strnstr(line, NAME_CMD_STRING, ft_strlen(line)) != 0)
		ret++;
	while (i >= 0 && ft_strnstr(line, g_op_tab[i].op, ft_strlen(line)) == 0)
		i--;
	if (i != -1)
		return (FALSE);
	i = 0;
	while (line[i])
	{
		if (strchr(LABEL_CHARS, line[i]) != 0)
			isnotok++;
		if (strchr(ALLOWED_CHARS, line[i]) != 0 && line[i] != ' ')
			isok++;
		i++;
	}
	if (ret == 0 && isok == 0 && isnotok != 0)
		return (TRUE);
	return (FALSE);
}
