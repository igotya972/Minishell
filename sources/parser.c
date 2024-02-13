/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afont <afont@student.42nice.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 16:28:46 by dferjul           #+#    #+#             */
/*   Updated: 2024/02/13 16:16:50 by afont            ###   ########.fr       */
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
	char	**tmp2;
	int 	i;
	int		j;
	
	tmp1 = ft_space_to_control(data->input);
	tmp1 = ft_var_to_value(tmp1, data);
	// printf("%s\n", tmp1);
	tmp1 = ft_del_quote(tmp1);
	tmp2 = ft_split(tmp1, ' ');
	free(tmp1);
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
	i = -1;
	while (data->lexer[++i])
		printf("%s\n", data->lexer[i]);
}

char	*ft_var_to_value(char *input, t_data *data)
{
	int		i;
	char	*result;
	
	i = 0;
	result = ft_strdup(input);
	while (result[i])
	{
		// printf("%d, %c\n", i, result[i]);
		if (result[i] == '$')
		{
			result = ft_replace_var(result, i, data, &i);
		}
		i++;
	}
	return (result);
}

char	*ft_replace_var(char *input, int i, t_data *data, int *len_value)
{
	char	*result;
	char	*value;
	char	*key;
	int		j;
	int		i_base;
	
	j = -1;
	i_base = i;
	while (input[i] && input[i] != ' ')
		i++;
	key = malloc(i);
	i = i_base;
	while (input[i] && input[i] != ' ' && input[i] != '"' && input[i] != 17)
		key[++j] = input[i++];
	key[j + 1] = 0;
	// printf("key + 1 = %s\n", key + 1);
	// write(1, "!", 1);
	value = ft_get_value(key + 1, data);
	// write(1, "!", 1);
	*len_value = ft_strlen(value) + i_base;
	// printf("value = %s\n", value);
	// write(1, "!", 1);
	result = ft_del_key(input, i_base);
	// printf("result = %s\n", result);
	result = ft_add_to_str(input, value, i_base, ft_strlen(key));
	// printf("result = %s\n", result);
	return (result);
}

char	*ft_del_key(char *input, int i)
{
	char	*result;
	int		j;
	
	j = -1;
	result = malloc(ft_strlen(input) + 1);
	while (++j < i)
		result[j] = input[j];
	j = -1;
	while (input[i] && input[i] != ' ')
		i++;
	while (input[i])
		result[++j] = input[i++];
	result[j + 1] = 0;
	return (result);
}

char	*ft_add_to_str(char *input, char *value, int i, int len_key)
{
	char	*tmp1;
	char	*tmp2;
	// int		j;
	
	// j = -1;	
	tmp1 = malloc(i);
	// printf("%s, %d\n", input, i);
	ft_strlcpy(tmp1, input, i + 1);
	// printf("%s\n", tmp1);
	tmp2 = malloc(ft_strlen(input + i + len_key) + 1);
	// printf("%s\n", input + i + len_key);
	tmp2 = ft_strdup(input + i + len_key);
	// printf("%s\n", tmp2);
	// printf("%s, %s, %s\n", tmp1, value, tmp2);
	if (value)
	{
		tmp1 = ft_strjoin(tmp1, value);
		tmp1 = ft_strjoin(tmp1, tmp2);
	}
	else
		tmp1 = ft_strjoin(tmp1, tmp2);
	return (tmp1);
}

char	*ft_get_value(char *key, t_data *data)
{
	int		i;
	char	*value;
	
	i = -1;
	value = NULL;
	while (data->export[++i].key)
	{
		if (ft_strcmp(data->export[i].key, key) == 0)
			value = ft_strdup(data->export[i].value);
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