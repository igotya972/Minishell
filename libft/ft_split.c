/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afont <afont@student.42nice.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 01:19:21 by dferjul           #+#    #+#             */
/*   Updated: 2024/02/19 12:39:20 by afont            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count_word(char const *s, char c )
{
	size_t	i;
	int		j;

	i = 0;
	j = 0;
	while (s[i])
	{
		if (s[i] != c)
		{
			j++;
			while (s[i] != c && s[i])
				i++;
		}
		else
			i++;
	}
	return (j);
}

static char	*ft_strcpy_malloc(char const *s, char c)
{
	unsigned int	i;
	char			*str;

	i = 0;
	while (s[i] != c && s[i])
		i++;
	if (!s)
		return (0);
	str = malloc(sizeof(char) * (i + 1));
	ft_protect_malloc(str);
	i = 0;
	while (s[i] && s[i] != c)
	{
		str[i] = s[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	**ft_split(char const *s, char c)
{
	unsigned int	i;
	unsigned int	j;
	unsigned int	n;
	char			**tab;

	i = 0;
	j = 0;
	n = ft_count_word(s, c);
	tab = malloc(sizeof(char *) * (n + 1));
	ft_protect_malloc(tab);
	while (s[i] && j < n)
	{
		if (s[i] != c)
		{
			tab[j] = ft_strcpy_malloc(s + i, c);
			j++;
			while (s[i] && s[i] != c)
				i++;
		}
		else
			i++;
	}
	tab[j] = NULL;
	return (tab);
}
