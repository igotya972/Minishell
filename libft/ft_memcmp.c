/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dferjul <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 10:36:58 by dferjul           #+#    #+#             */
/*   Updated: 2022/11/21 12:14:14 by dferjul          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*s;
	unsigned char	*c;
	unsigned int	i;

	s = (unsigned char *)s1;
	c = (unsigned char *)s2;
	i = 0;
	if (n == 0)
		return (0);
	while (s[i] == c[i] && i < (n - 1))
		i++;
	return (s[i] - c[i]);
}
