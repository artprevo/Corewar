/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artprevo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/11 17:35:08 by artprevo          #+#    #+#             */
/*   Updated: 2018/11/12 19:55:34 by artprevo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return ;
	while (i < n)
	{
		((char *)s)[i] = 0;
		i++;
	}
}
