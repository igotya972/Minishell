/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afont <afont@student.42nice.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 16:28:46 by dferjul           #+#    #+#             */
/*   Updated: 2024/02/13 09:48:07 by afont            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	lexer(t_data *data)
{
	char	*tmp1;
	char	**tmp2;
	int 	i;
	int		j;
	
	tmp1 = ft_space_to_control(data->input);
	tmp1 = ft_del_quote(tmp1);
	tmp2 = ft_split(tmp1, ' ');
	i = -1;
	while (tmp2[++i])
	{
		j = -1;
		while (tmp2[i][++j])
		{
			if (tmp2[i][j] == 17)
				tmp2[i][j] = ' ';
		}
	}
	data->lexer = tmp2;
}

char	*ft_del_quote(char *input)
{
	char	*result;
	int		i;
	int		j;

	i = -1;
	j = -1;
	result = malloc(ft_strlen(input));
	while (input[++i])
		if (input[i] != '"')
			result[++j] = input[i];
	result[j + 1] = 0;
	free(input);
	return (result);
}

char	*ft_space_to_control(char *input)
{
	char	*result;
	int		i;
	
	i = 0;
	result = malloc(sizeof(char) * ft_strlen(input) + 1);
	while (input[i])
	{
		
		if (input[i] == ' ' && ft_is_in_quotes(input, i) == 1)
			result[i] = 17;
		else
			result[i] = input[i];
		i++;
	}
	result[i] = 0;
	return (result);
}

int		ft_is_in_quotes(char *input, int i)
{
	int		j;
	int		flag;

	j = 0;
	flag = 0;
	while (input[j])
	{
		if (input[j] == '"')
		{
			if (flag == 0)
				flag = 1;
			else
				flag = 0;
		}
		if (j == i && flag == 1)
			return (1);
		j++;
	}
	return (0);
}