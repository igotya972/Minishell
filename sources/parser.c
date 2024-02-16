/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afont <afont@student.42nice.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 16:28:46 by dferjul           #+#    #+#             */
/*   Updated: 2024/02/16 16:39:34 by afont            ###   ########.fr       */
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
	int 	i;
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
		// printf("start = %s, %d, %c\n", result, i, result[i]);
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
	while (input[i] && input[i] != ' ' && input[i] != '"' && input[i] != 17 && input[i] != '\''  && input[i] != '$')
		i++;
	key = malloc(i + 1 - i_base);
	i = i_base;
	while (input[++i] && input[i] != ' ' && input[i] != '"' && input[i] != 17 && input[i] != '\''  && input[i] != '$')
	{
		key[++j] = input[i];
	}
	key[j + 1] = 0;
	// printf("key : %s\n", key);
	value = ft_get_value(key, data);
	// printf("value : %s\n", value);
	*len_value = ft_strlen(value) + i_base - 1;
	// printf("len value = %d\n", *len_value);
	result = ft_add_to_str(input, value, i_base, ft_strlen(key));
	// printf("result = %s\n", result);
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
	ft_strlcpy(tmp1, input, i + 1);
	// printf("tmp1 = %s\n", tmp1);
	tmp3 = ft_strdup(input + i + len_key + 1);
	// printf("tmp3 = %s\n", tmp3);
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
		// printf("%s, %s\n", data->export[i].key, key);
		if (ft_strcmp(data->export[i].key, key) == 0)
		{
			if (!data->export[i].value)
			{
				value = ft_strdup("");
				break;
			}
			// value = ft_strdup(data->export[i].value);
			j = 0;
			k = -1;
			value = malloc(ft_strlen(data->export[i].value) + 1);
			while ((data->export[i].value)[++j + 1])
				value[++k] = (data->export[i].value)[j];
			value[k + 1] = 0;
			break;
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
	while (input[++i])
	{
		// printf("%c, %d\n", input[i], ft_is_in_quotes(input, i));
		// printf("%d, %d, %d\n", input[i] != '"',  input[i] != '\'', ft_is_in_quotes(input, i) == 1);
		if ((input[i] != '"' && input[i] != '\'') || ft_is_in_quotes(input, i) != 0)
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

int		ft_is_in_quotes(char *input, int i)
{
	int		j;
	int		flag;
	int		anti_start_quote;

	j = 0;
	flag = 0;
	anti_start_quote = 0;
	// printf("%s\n", input);
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
		// printf("%c, %d\n", input[j], flag);
		if (j == i && (flag == 1 || flag == 2) && anti_start_quote != 1)
			return (flag);
		anti_start_quote = 0;
		j++;
	}
	return (0);
}

int		ft_is_in_Squotes(char *input, int i)
{
	int		j;
	int		flag;
	
	j = 0;
	flag = 0;
	while (input[j])
	{
		
		if (input[j] == '\'')
		{
			if (flag == 0)
				flag = 1;
			else if (flag == 1)
				flag = 0;
		}
		if (j == i && flag == 1)
			return (1);
		j++;
	}
	return (0);
}