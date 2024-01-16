/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dferjul <dferjul@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 16:28:46 by dferjul           #+#    #+#             */
/*   Updated: 2024/01/12 23:56:56 by dferjul          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	lexer_temporaire(t_data *data)
{
	// ne pas split entre les guillemets ("salut                   s")
	data->lexer = ft_split(data->input, ' ');
}

/* int		count_tokens(t_data *data)
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
		if (data->input[i] != ' ' && init_token == 0 )
		{
			init_token = 1;
			count++;
		}
		else if (data->input[i] == ' ')
			init_token = 0;
		i++;
	}
	return (count);
} */

/* char		*append_char_to_token(char **token, char c)
{
	int		i;
	int		len;
	char	*token_bis;

	//token_bis = malloc(sizeof char*) * (ft_strlen(token)) + 1);
} */

/* char	**lexer(t_data *data)
{
	//char	**tab;
	int		i;
	int		j;

	//tab = malloc(sizeof(char *) * (count_tokens(data->input) + 1));
	if (!tab)
	{
		perror("Erreur d'allocation de mémoire");
		exit(EXIT_FAILURE);
	}
	i = 0;
	j = 0;
	while (data->input[i])
	{
		while (data->input[i] && data->input[i] != ' ')
		{
			//tab[j] = append_char_to_token(tab[j], input);
			i++;
		}
		j++;
		while (data->input[i] == ' ')
			i++;
	}
	//tab[j] = NULL;
	return (tab);
} */
