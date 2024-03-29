/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afont <afont@student.42nice.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 16:28:46 by dferjul           #+#    #+#             */
/*   Updated: 2024/03/19 16:44:48 by afont            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	lexer(t_data *data)
{
	char	*tmp1;
	char	*tmp2;
	char	**tmp3;
	int		i;
	int		j;

	tmp1 = ft_space_to_control(data->input);
	tmp2 = ft_delimiteur(tmp1);
	tmp1 = ft_var_to_value(tmp2, data);
	tmp2 = ft_delimiteur_to_control(tmp1);
	tmp1 = ft_del_quote(tmp2);
	tmp3 = ft_split(tmp1, ' ');
	free(tmp1);
	i = -1;
	while (tmp3[++i])
	{
		j = -1;
		while (tmp3[i][++j])
			if (tmp3[i][j] == 17)
				tmp3[i][j] = ' ';
	}
	data->lexer = tmp3;
}

char	*ft_del_quote(char *input)
{
	char	*result;
	int		i;
	int		j;

	i = -1;
	j = -1;
	result = malloc(ft_strlen(input) + 1);
	ft_protect_malloc(result);
	while (input[++i])
	{
		if ((input[i] != '"' && input[i] != '\'') \
		|| ft_is_in_quotes(input, i) != 0)
			result[++j] = input[i];
	}
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
	ft_protect_malloc(result);
	while (input[i])
	{
		if (input[i] == ' ' && ft_is_in_quotes(input, i) != 0)
			result[i] = 17;
		else
			result[i] = input[i];
		i++;
	}
	result[i] = 0;
	return (result);
}

int	ft_is_in_quotes(char *input, int i)
{
	int		j;
	int		flag;
	int		anti_start_quote;

	j = 0;
	flag = 0;
	anti_start_quote = 0;
	while (input[j])
	{
		if (input[j] == '"')
			ft_flag_dquote(&flag, &anti_start_quote);
		else if (input[j] == '\'')
			ft_flag_squote(&flag, &anti_start_quote);
		if (j == i && (flag == 1 || flag == 2) && anti_start_quote != 1)
			return (flag);
		anti_start_quote = 0;
		j++;
	}
	return (0);
}
