/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afont <afont@student.42nice.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 16:13:16 by afont             #+#    #+#             */
/*   Updated: 2024/03/19 16:38:16 by afont            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

char	*ft_replace_var(char *input, int i, t_data *data, int *len_value)
{
	char	*result;
	char	*value;
	char	*key;
	int		i_base;

	i_base = i;
	key = ft_key_to_replace(input, i, i_base);
	value = ft_get_value(key, data);
	*len_value = ft_strlen(value) + i_base - 1;
	result = ft_add_to_str(input, value, i_base, ft_strlen(key));
	free(key);
	free(input);
	free(value);
	return (result);
}

char	*ft_var_to_value(char *input, t_data *data)
{
	int		i;
	char	*result;

	i = -1;
	result = ft_strdup(input);
	while (++i < (int)ft_strlen(result) && result[i])
		if (result[i] == '$' && ft_is_in_quotes(result, i) != 2 && \
		!is_parser_delimiteur(result[i]) && result[i + 1] && \
		result[i + 1] != ' ' && result[i + 1] != '\"' && \
		result[i + 1] != '\'')
			result = ft_replace_var(result, i, data, &i);
	free(input);
	return (result);
}

char	*ft_delimiteur(char *input)
{
	char	*tmp;
	int		i;
	int		j;

	tmp = malloc((nbr_parser_delimiteur(input) * 2) + ft_strlen(input) + 1);
	ft_protect_malloc(tmp);
	i = -1;
	j = -1;
	while (input[++i])
	{
		if (is_parser_delimiteur(input[i]) && ft_is_in_quotes(input, i) == 0)
			delimiteur_modifier(tmp, input, &i, &j);
		else
			tmp[++j] = input[i];
	}
	tmp[j + 1] = 0;
	free(input);
	return (tmp);
}

int	check_parse_error(char **input)
{
	int		i;

	i = -1;
	if (input[0] && !ft_strcmp(input[0], "|"))
	{
		printf("Minishell: parse error near `|'\n");
		g_error = 2;
		return (1);
	}
	while (input[++i])
		if (check_parse_error2(input, i))
			return (1);
	return (0);
}
