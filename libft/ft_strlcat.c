/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dferjul <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 15:54:26 by dferjul           #+#    #+#             */
/*   Updated: 2022/11/28 22:26:58 by dferjul          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	unsigned int	i;
	unsigned int	len;
	int				in;

	i = 0;
	in = 0;
	len = 0;
	while (src[in])
		in++;
	if (!dstsize)
		return (in);
	while (dst[len] && len < dstsize)
		len++;
	i = len;
	while (src[len - i] && len < dstsize - 1)
	{
		dst[len] = src[len - i];
		len++;
	}
	if (i < dstsize)
		dst[len] = '\0';
	return (i + in);
}
