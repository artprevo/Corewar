/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoinf.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artprevo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/18 20:53:25 by artprevo          #+#    #+#             */
/*   Updated: 2019/09/26 17:58:30 by artprevo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoinf_l(char *s1, char *s2)
{
	char		*stack;
	int			i;
	int			j;

	if (!(stack = ft_memalloc(ft_strlen(s1) + ft_strlen(s2) + 1)))
		return (NULL);
	i = -1;
	j = -1;
	while (s1[++i])
		stack[i] = s1[i];
	while (s2[++j])
		stack[i + j] = s2[j];
	ft_strdel(&s1);
	return (stack);
}
