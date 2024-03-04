/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afont <afont@student.42nice.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 00:23:59 by dferjul           #+#    #+#             */
/*   Updated: 2024/02/19 13:27:24 by afont            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*c;

	if (count > SIZE_MAX)
		return (NULL);
	c = malloc(count * size);
	ft_protect_malloc(c);
	ft_bzero(c, count * size);
	return (c);
}
