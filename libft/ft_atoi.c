/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artprevo <artprevo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/09 16:19:45 by artprevo          #+#    #+#             */
/*   Updated: 2020/08/02 16:09:08 by artprevo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		if_bullshit(long result, long neg, char c)
{
	if (result * 10 + (c - 48) < result)
	{
		if (neg == -1)
			return (UINT_MAX + 1);
		else
			return (UINT_MAX);
	}
	else
		return (0);
}

int				ft_atoi(const char *str)
{
	long	i;
	long	result;
	long	neg;

	i = 0;
	result = 0;
	neg = 1;
	while (str[i] && (str[i] == '\t' || str[i] == '\n' || str[i] == '\r' ||
	str[i] == '\v' || str[i] == '\f'
		|| str[i] == ' '))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			neg = -1;
		i++;
	}
	while (ft_isdigit(str[i]) == 1)
	{
		if (if_bullshit(result, neg, str[i]) != 0)
			return ((int)if_bullshit(result, neg, str[i]));
		result = result * 10 + (str[i] - 48);
		i++;
	}
	return (result * neg);
}
