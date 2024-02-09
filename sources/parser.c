/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afont <afont@student.42nice.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 16:28:46 by dferjul           #+#    #+#             */
/*   Updated: 2024/02/09 18:00:39 by afont            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	lexer_temporaire(t_data *data)
{
	data->lexer = ft_split(data->input, ' ');
}

void	lexer(t_data *data)
{
	char	**tmp_lexer;
	int		i;
	int		j;
	int		flag;

	flag = 0;
	i = -1;
	// ft_count_guillemets(data->input);
	// ft_count_lexer_words(data->input);
	//printf ("malloc : %d\n", (ft_count_guillemets(data->input) + ft_count_lexer_words(data->input) + 1));
	j = (ft_count_guillemets(data->input) + ft_count_lexer_words(data->input) + 1);
	tmp_lexer = malloc(sizeof(char *) * j);
	while (++i < j)
		tmp_lexer[i] = NULL;
	i = -1;
	j = 0;
	while (data->input[++i])
	{
		write(1, "!", 1);
		if (data->input[i] == '"' && flag == 0)
		{
			write(1, "1", 1);
			j++;
			flag = 1;
		}
		else if (data->input[i] == '"' && flag == 1)
		{
			write(1, "2", 1);
			flag = 0;
		}
		else if (data->input[i] == ' ' && data->input[i + 1] != '"' && flag == 0)
		{
			write(1, "3", 1);
			// if (data->input[i + 1] == ' ')
			// {
				while (data->input[i] && data->input[i] == ' ' && data->input[i + 1] != '"')
				{
					write(1, "4", 1);
					i++;
				}
			// }
			i--;
			j++;
		}
		else if (data->input[i] == ' ' && flag == 1)
		{
			write(1, "5", 1);
			tmp_lexer[j] = ft_strjoin_carac(tmp_lexer[j], ' ');
		}
		else
		{
			write(1, "6", 1);
			tmp_lexer[j] = ft_strjoin_carac(tmp_lexer[j], data->input[i]);
		}
		write(1, "\n", 1);
	}
	tmp_lexer[j + 1] = NULL;
	data->lexer = tmp_lexer;
	i = -1;
	while (data->lexer[++i])
		printf("%s\n", data->lexer[i]);
}

int		ft_count_lexer_words(char *input)
{
	int	cmp;
	int	i;

	i = 0;
	cmp = 0;
	while (input[i] == ' ')
		i++;
	while (input[i])
	{
		while (input[i] && input[i] == ' ')
			i++;
		if (input[i] == '"')
		{
			i++;
			while (input[i] && input[i] != '"')
				i++;
			if (input[i + 1])
				i++;
			else
			{
				printf("%d\n", cmp);
				return (cmp);
			}
		}
		else if (input[i] && input[i] != ' ')
		{
			cmp++;
			while (input[i] && input[i] != ' ')
				i++;
		}
	}
	printf("%d\n", cmp);
	return (cmp);
}

int	ft_count_guillemets(char *input)
{
	int	result;
	int	i;

	i = 0;
	result = 0;
	printf("%s\n", input);
	while (input[i])
	{
		if (input[i] == '"')
			result++;
		i++;
	}
	printf("%d\n", result / 2);
	return (result / 2);
}

		// if (input[i] == '"')
		// {
		// 	i++;
		// 	while (input[i] && input[i] != '"')
		// 		i++;
		// 	if (input[i + 1])	
		// 		i++;
		// 	else
		// 		return (result);
		// }