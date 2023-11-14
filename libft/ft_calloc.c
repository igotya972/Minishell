/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dferjul <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 00:23:59 by dferjul           #+#    #+#             */
/*   Updated: 2022/11/23 22:12:36 by dferjul          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*c;

	if (count > SIZE_MAX)
		return (NULL);
	c = malloc (count * size);
	if (!c)
		return (0);
	ft_bzero (c, count * size);
	return (c);
}
