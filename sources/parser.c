/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dferjul <dferjul@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 16:28:46 by dferjul           #+#    #+#             */
/*   Updated: 2024/01/18 05:25:09 by dferjul          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	lexer_temporaire(t_data *data)
{
	// ne pas split entre les guillemets ("salut                   s")
	data->lexer = ft_split(data->input, ' ');
}

int	count_tokens(t_data *data)
{
	int		i;
	int		count;
	int		init_token;

	i = 0;
	count = 0;
	init_token = 0;
	while (data->input[i])
	{
		// skip <<">>
		if (data->input[i] == 34)
			i++;
		if (data->input[i] != ' ' && init_token == 0)
		{
			init_token = 1;
			count++;
		}
		else if (data->input[i] == ' ')
			init_token = 0;
		i++;
	}
	return (count);
}

char	*append_char_to_token(char **token, char c)
{
	int		i;
	int		len;
	char	*token_bis;

	len = ft_strlen(*token);
	token_bis = malloc(sizeof(char *) * (len + 2));
	if (token_bis == NULL)
	{
		perror("Error malloc token");
		exit(EXIT_FAILURE);
	}
	while (i < len)
	{
		token_bis[i] = (*token)[i];
		i++;
	}
	token_bis[len] = c;
	token_bis[len + 1] = '\0';
	free(*token);
	*token = token_bis;
	return (*token);
}

char	**lexer(t_data *data)
{
	char	**tab;
	int		i;
	int		j;

	tab = malloc(sizeof(char *) * (count_tokens(data) + 1));
	data->lexer = ft_split(data->input, ' ');
	i = -1;
	while (tab[++i])
		printf("%d %s\n", i, tab[i]);
	if (!tab)
	{
		perror("Erreur d'allocation de mémoire");
		exit(EXIT_FAILURE);
	}
	j = 0;
	while (data->input[++i])
	{
		while (data->input[i] && data->input[i] != ' ')
			tab[j] = append_char_to_token(&tab[j], data->input[i]);
		j++;
		while (data->input[i] == ' ')
			i++;
	}
	tab[j] = NULL;
	return (data->lexer);
}
