/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artprevo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/09 17:56:08 by artprevo          #+#    #+#             */
/*   Updated: 2018/11/22 19:28:26 by artprevo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s)
{
	int			i;
	int			j;
	int			len;
	char		*str;

	i = 0;
	len = 0;
	if (!s)
		return (NULL);
	j = ft_strlen(s) - 1;
	while (s[i] == ' ' || s[i] == '\n' || s[i] == '\t')
		i++;
	while (s[j] == ' ' || s[j] == '\n' || s[j] == '\t')
		j--;
	if (j < i)
	{
		i = 1;
		j = 0;
	}
	if (!(str = (char *)malloc(sizeof(char) * (j - i + 2))))
		return (NULL);
	while (i <= j)
		str[len++] = s[i++];
	str[len] = '\0';
	return (str);
}
