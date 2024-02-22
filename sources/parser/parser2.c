/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afont <afont@student.42nice.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 16:11:13 by afont             #+#    #+#             */
/*   Updated: 2024/02/22 10:27:13 by afont            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ft_get_value(char *key, t_data *data)
{
	int		i;
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
			value = ft_copy_value(data, i);
			break ;
		}
	}
	return (value);
}

char	*ft_key_to_replace(char *input, int i, int *i_base)
{
	char	*key;
	int		j;

	j = -1;
	*i_base = i;
	i++;
	while (input[i] && input[i] != ' ' && input[i] != '"' \
	&& input[i] != 17 && input[i] != '\'' && input[i] != '$')
		i++;
	key = malloc(i + 1 - *i_base);
	ft_protect_malloc(key);
	i = *i_base;
	while (input[++i] && input[i] != ' ' && input[i] != '"' \
	&& input[i] != 17 && input[i] != '\'' && input[i] != '$')
		key[++j] = input[i];
	key[j + 1] = 0;
	return (key);
}

char	*ft_copy_value(t_data *data, int i)
{
	int		j;
	int		k;
	char	*value;

	j = 0;
	k = -1;
	value = malloc(ft_strlen(data->export[i].value) + 1);
	ft_protect_malloc(value);
	while ((data->export[i].value)[++j + 1])
		value[++k] = (data->export[i].value)[j];
	value[k + 1] = 0;
	return (value);
}

void	ft_flag_dquote(int *flag, int *anti_start_quote)
{
	if (*flag == 0)
	{
		*flag = 1;
		*anti_start_quote = 1;
	}
	else if (*flag == 1)
		*flag = 0;
}

void	ft_flag_squote(int *flag, int *anti_start_quote)
{
	if (*flag == 0)
	{
		*flag = 2;
		*anti_start_quote = 1;
	}
	else if (*flag == 2)
		*flag = 0;
}
