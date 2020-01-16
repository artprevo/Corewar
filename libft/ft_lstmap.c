/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artprevo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/24 11:42:54 by artprevo          #+#    #+#             */
/*   Updated: 2018/11/24 12:03:16 by artprevo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*flist;
	t_list	*p;

	if (!lst || !f)
		return (NULL);
	flist = f(lst);
	p = flist;
	while (lst->next)
	{
		lst = lst->next;
		p->next = f(lst);
		p = p->next;
	}
	free(p);
	return (flist);
}
