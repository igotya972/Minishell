/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afont <afont@student.42nice.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 00:04:37 by dferjul           #+#    #+#             */
/*   Updated: 2024/02/19 12:38:51 by afont            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_digit(long int n)
{
	int	i;

	i = 0;
	if (n < 0)
		n *= -1;
	if (n < 10)
		return (1);
	while (n)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

char	*ft_numeric(char *str, long int s)
{
	int	i;

	i = ft_digit(s);
	if (s == 0)
	{
		str[0] = '0';
		str[i] = '\0';
		return (str);
	}
	if (s < 0)
	{
		s *= -1;
		str[0] = '-';
		i += 1;
	}
	while (s != 0)
	{
		str[i - 1] = s % 10 + 48;
		s = s / 10;
		i--;
	}
	return (str);
}

char	*ft_itoa(int n)
{
	int			i;
	char		*str;
	long int	c;

	c = n;
	i = ft_digit(n);
	if (c >= 0)
	{
		str = malloc(sizeof(char) * (i + 1));
		ft_protect_malloc(str);
		str[i] = '\0';
	}
	else
	{
		str = malloc(sizeof(char) * (i + 2));
		ft_protect_malloc(str);
		str[i + 1] = '\0';
	}
	str = ft_numeric(str, c);
	return (str);
}
