/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artprevo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/24 11:20:16 by artprevo          #+#    #+#             */
/*   Updated: 2018/11/24 11:28:40 by artprevo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void const *content, size_t content_size)
{
	t_list	*p;

	if (!(p = malloc(sizeof(*p))))
		return (NULL);
	if (content == NULL)
	{
		p->content = NULL;
		p->content_size = 0;
	}
	else
	{
		if (!(p->content = malloc(content_size)))
			return (NULL);
		p->content_size = content_size;
		ft_memcpy(p->content, content, content_size);
	}
	p->next = NULL;
	return (p);
}
