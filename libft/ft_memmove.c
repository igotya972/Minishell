/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dferjul <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/20 14:21:15 by dferjul           #+#    #+#             */
/*   Updated: 2022/11/28 22:34:09 by dferjul          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*d;
	unsigned char	*s;
	unsigned int	i;

	i = 0;
	s = (unsigned char *) src;
	d = (unsigned char *) dst;
	if (!d && !s)
		return (0);
	if (d > s)
	{
		while (len > 0)
		{
			len--;
			d[len] = s[len];
		}
		return (d);
	}
	while (i < len)
	{
		d[i] = s[i];
		i++;
	}
	return (d);
}
