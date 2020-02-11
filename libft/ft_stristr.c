/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artprevo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/09 14:55:45 by artprevo          #+#    #+#             */
/*   Updated: 2018/11/22 14:18:46 by artprevo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			ft_stristr(const char *haystack, const char *needle, size_t len)
{
	size_t i;
	size_t j;

	i = 0;
	j = 0;
	if (ft_strlen(needle) == 0)
		return (0);
	while (haystack[i])
	{
		while (needle[j] == haystack[i + j] && (i + j) < len)
		{
			if (j == (ft_strlen(needle) - 1))
				return (i + j + 1);
			j++;
		}
		j = 0;
		i++;
	}
	return (0);
}
