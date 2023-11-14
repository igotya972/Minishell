/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dferjul <dferjul@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 21:06:24 by dferjul           #+#    #+#             */
/*   Updated: 2023/01/26 16:28:10 by dferjul          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*nlist;
	t_list	*new;

	if (!lst || !del || !f)
		return (0);
	nlist = ft_lstnew(lst->content);
	if (!nlist)
		return (NULL);
	nlist->content = f(nlist->content);
	new = nlist;
	while (lst->next != 0)
	{
		lst = lst->next;
		new->next = ft_lstnew(lst->content);
		if (!new->next)
		{
			ft_lstclear(&nlist, del);
			return (NULL);
		}
		new->next->content = f(new->next->content);
		new = new->next;
	}
	return (nlist);
}
