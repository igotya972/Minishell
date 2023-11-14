/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dferjul <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 04:12:18 by dferjul           #+#    #+#             */
/*   Updated: 2023/01/18 14:44:47 by dferjul          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*ncontent;

	ncontent = (t_list *)malloc(sizeof(t_list));
	if (!ncontent)
		return (NULL);
	ncontent -> content = content;
	ncontent -> next = NULL;
	return (ncontent);
}
