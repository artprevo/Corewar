/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artprevo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/09 16:19:45 by artprevo          #+#    #+#             */
/*   Updated: 2019/09/21 17:35:25 by artprevo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#define S str[i]

int	ft_atoi(const char *str)
{
	int	i;
	int	result;
	int neg;

	i = 0;
	result = 0;
	neg = 1;
	while (S && (S == '\t' || S == '\n' || S == '\r' || S == '\v' || S == '\f'
		|| S == ' '))
		i++;
	if (S == '+' || S == '-')
	{
		if (S == '-')
			neg = -1;
		i++;
	}
	while (ft_isdigit(S) == 1)
	{
		result = result * 10 + (S - 48);
		i++;
	}
	return (result * neg);
}
