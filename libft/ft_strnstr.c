/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dferjul <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/20 14:43:24 by dferjul           #+#    #+#             */
/*   Updated: 2022/11/29 00:27:04 by dferjul          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strnstr(const char *hs, const char *n, size_t len)
{
	size_t	i;
	size_t	in;

	i = 0;
	in = 0;
	if (!n[0])
		return ((char *)hs);
	while (hs[i] && (i + in < len))
	{
		if (hs[i] && hs[i] == n[0])
		{
			while (n[in] && hs[i + in] == n[in] && (i + in < len))
				in++;
			if (n[in] == '\0')
				return ((char *)hs + i);
		}
		i++;
	}
	return (0);
}
