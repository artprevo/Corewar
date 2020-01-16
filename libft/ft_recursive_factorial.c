/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_recursive_factorial.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artprevo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/04 15:23:44 by artprevo          #+#    #+#             */
/*   Updated: 2018/09/05 13:47:38 by artprevo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_recursive_factorial(int nb)
{
	if (nb <= 12 && nb >= -12 && nb != 0)
	{
		if (nb <= 0)
			nb *= ft_recursive_factorial(nb + 1);
		else
			nb *= ft_recursive_factorial(nb - 1);
	}
	else
	{
		if (nb == 0)
			nb = 1;
		else
			nb = 0;
	}
	return (nb);
}
