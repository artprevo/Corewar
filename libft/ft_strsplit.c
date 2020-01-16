/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artprevo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/11 14:51:49 by artprevo          #+#    #+#             */
/*   Updated: 2018/11/22 19:31:22 by artprevo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	**ft_malloc(char **tab, const char *s, char c)
{
	int	i;
	int	j;
	int	k;

	k = 0;
	i = 0;
	while (s[i])
	{
		j = 0;
		while (s[i] != c && s[i])
		{
			i++;
			j++;
		}
		if (j != 0)
		{
			if (!(tab[k] = (char *)malloc(sizeof(char) * (j + 1))))
				return (NULL);
			k++;
		}
		if (s[i])
			i++;
	}
	return (tab);
}

static void	ft_fill(char **tab, char const *s, char c)
{
	int i;
	int j;
	int k;

	k = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] != c)
		{
			j = 0;
			while (s[i] != c && s[i])
				tab[k][j++] = s[i++];
			tab[k++][j] = '\0';
		}
		if (s[i])
			i++;
	}
	tab[k] = NULL;
}

char		**ft_strsplit(char const *s, char c)
{
	int		i;
	int		j;
	char	**tab;

	i = 0;
	j = 0;
	if (!s)
		return (NULL);
	while (s[i])
	{
		if (s[i] != c && (s[i + 1] == c || s[i + 1] == '\0'))
			j++;
		i++;
	}
	if (!(tab = (char **)malloc(sizeof(char *) * (j + 1))))
		return (NULL);
	if (!(tab = ft_malloc(tab, s, c)))
		return (NULL);
	ft_fill(tab, s, c);
	return (tab);
}
