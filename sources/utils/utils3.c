/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afont <afont@student.42nice.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 13:17:24 by afont             #+#    #+#             */
/*   Updated: 2024/03/19 13:17:55 by afont            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**ft_remove_control_tab(char **str)
{
	int		i;
	int		j;
	int		k;
	char	**tmp;

	i = 0;
	while (str[i])
		i++;
	tmp = malloc(sizeof(char *) * (i + 1));
	i = -1;
	while (str[++i])
	{
		j = -1;
		k = -1;
		tmp[i] = malloc(sizeof(char) * (ft_strlen(str[i]) + 1));
		while (str[i][++j])
			if (str[i][j] != 18)
				tmp[i][++k] = str[i][j];
		tmp[i][++k] = '\0';
	}
	tmp[i] = NULL;
	ft_free_tab(str);
	return (tmp);
}

char	*ft_remove_control(char *str)
{
	int		i;
	int		j;
	char	*tmp;

	tmp = malloc(sizeof(char) * (ft_strlen(str) + 1));
	i = -1;
	j = -1;
	if (!str)
		return (tmp);
	while (str[++i])
		if (str[i] != 18)
			tmp[++j] = str[i];
	tmp[++j] = '\0';
	return (tmp);
}

int	ft_atoi_simple(char *str)
{
	int	i;
	int	result;

	i = 0;
	result = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	while (str[i] && (str[i] >= '0' && str[i] <= '9'))
	{
		result += (str[i] - 48);
		i++;
		if (!(str[i] < '0' || str[i] > '9'))
			result *= 10;
	}
	if (str[i] && (str[i] < '0' || str[i] > '9'))
		return (-1);
	return (result);
}

int	is_pipe(char **lexer)
{
	int	i;

	i = -1;
	while (lexer[++i])
		if (ft_strcmp(lexer[i], "|") == 0)
			return (1);
	return (0);
}
