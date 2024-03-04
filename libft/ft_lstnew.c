/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afont <afont@student.42nice.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 04:12:18 by dferjul           #+#    #+#             */
/*   Updated: 2024/02/19 12:41:21 by afont            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*ncontent;

	ncontent = (t_list *)malloc(sizeof(t_list));
	ft_protect_malloc(ncontent);
	ncontent -> content = content;
	ncontent -> next = NULL;
	return (ncontent);
}
