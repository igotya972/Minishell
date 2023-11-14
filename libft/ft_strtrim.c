/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dferjul <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 18:34:46 by dferjul           #+#    #+#             */
/*   Updated: 2022/11/28 20:13:01 by dferjul          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_skip_first_word(char const *s1, char const *set)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (s1[i] && set[j])
	{
		if (s1[i] == set[j])
		{
			i++;
			j = 0;
		}
		else
		j++;
	}
	return (i);
}

static int	ft_count_str(char const *s1, char const *set)
{
	int	i;
	int	j;

	i = ft_strlen(s1);
	j = ft_strlen(set);
	while (i >= 0 && j >= 0)
	{
		if (s1[i] == set[j])
		{
			i--;
			j = ft_strlen(set);
		}
		else
			j--;
	}
	return (i);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*str;
	int		i;
	int		j;
	int		n;

	j = ft_count_str(s1, set);
	i = ft_skip_first_word(s1, set);
	n = 0;
	if (i > j || ft_strlen(s1) == 0)
	{
		str = malloc(sizeof(str) * (1));
		*str = '\0';
		return (str);
	}
	else
	str = malloc(sizeof(char) * (j - i + 2));
	if (!str)
		return (0);
	while (i <= j)
		str[n++] = s1[i++];
	str[n] = '\0';
	return (str);
}
