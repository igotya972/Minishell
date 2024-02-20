/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afont <afont@student.42nice.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 16:28:46 by dferjul           #+#    #+#             */
/*   Updated: 2024/02/19 13:44:56 by afont            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	lexer_temporaire(t_data *data)
{
	data->lexer = ft_split(data->input, ' ');
}

void	lexer(t_data *data)
{
	char	*tmp1;
	char	*tmp2;
	char	**tmp3;
	int		i;
	int		j;

	tmp1 = ft_space_to_control(data->input);
	tmp2 = ft_var_to_value(tmp1, data);
	free(tmp1);
	tmp1 = ft_del_quote(tmp2);
	tmp3 = ft_split(tmp1, ' ');
	free(tmp1);
	i = -1;
	while (tmp3[++i])
	{
		j = -1;
		while (tmp3[i][++j])
		{
			if (tmp3[i][j] == 17)
				tmp3[i][j] = ' ';
		}
	}
	data->lexer = tmp3;
}

char	*ft_var_to_value(char *input, t_data *data)
{
	int		i;
	char	*result;

	i = 0;
	result = ft_strdup(input);
	while (i < (int)ft_strlen(result) && result[i])
	{
		if (result[i] == '$' && ft_is_in_quotes(result, i) != 2)
			result = ft_replace_var(result, i, data, &i);
		i++;
	}
	return (result);
}

char	*ft_replace_var(char *input, int i, t_data *data, int *len_value)
{
	char	*result;
	char	*value;
	char	*key;
	int		i_base;
	int		j;

	j = -1;
	i_base = i;
	i++;
	while (input[i] && input[i] != ' ' && input[i] != '"' \
	&& input[i] != 17 && input[i] != '\'' && input[i] != '$')
		i++;
	key = malloc(i + 1 - i_base);
	ft_protect_malloc(key);
	i = i_base;
	while (input[++i] && input[i] != ' ' && input[i] != '"' \
	&& input[i] != 17 && input[i] != '\'' && input[i] != '$')
	{
		key[++j] = input[i];
	}
	key[j + 1] = 0;
	value = ft_get_value(key, data);
	*len_value = ft_strlen(value) + i_base - 1;
	result = ft_add_to_str(input, value, i_base, ft_strlen(key));
	free(key);
	free(input);
	free(value);
	return (result);
}

char	*ft_add_to_str(char *input, char *value, int i, int len_key)
{
	char	*tmp1;
	char	*tmp2;
	char	*tmp3;

	tmp1 = malloc(i + 1);
	ft_protect_malloc(tmp1);
	ft_strlcpy(tmp1, input, i + 1);
	tmp3 = ft_strdup(input + i + len_key + 1);
	if (value)
	{
		tmp2 = ft_strjoin(tmp1, value);
		free(tmp1);
		tmp1 = ft_strjoin(tmp2, tmp3);
		free(tmp2);
		free(tmp3);
		return (tmp1);
	}
	else
	{
		tmp2 = ft_strjoin(tmp1, tmp3);
		free(tmp3);
		free(tmp1);
		return (tmp2);
	}
}

char	*ft_get_value(char *key, t_data *data)
{
	int		i;
	int		j;
	int		k;
	char	*value;

	i = -1;
	value = NULL;
	while (data->export[++i].key)
	{
		if (ft_strcmp(data->export[i].key, key) == 0)
		{
			if (!data->export[i].value)
			{
				value = ft_strdup("");
				break ;
			}
			j = 0;
			k = -1;
			value = malloc(ft_strlen(data->export[i].value) + 1);
			ft_protect_malloc(value);
			while ((data->export[i].value)[++j + 1])
				value[++k] = (data->export[i].value)[j];
			value[k + 1] = 0;
			break ;
		}
	}
	return (value);
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
		{
			if (flag == 0)
			{
				flag = 1;
				anti_start_quote = 1;
			}
			else if (flag == 1)
				flag = 0;
		}
		else if (input[j] == '\'')
		{
			if (flag == 0)
			{
				flag = 2;
				anti_start_quote = 1;
			}
			else if (flag == 2)
				flag = 0;
		}
		if (j == i && (flag == 1 || flag == 2) && anti_start_quote != 1)
			return (flag);
		anti_start_quote = 0;
		j++;
	}
	return (0);
}
