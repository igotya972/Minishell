/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dferjul <dferjul@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 16:19:14 by dferjul           #+#    #+#             */
/*   Updated: 2024/01/12 16:19:15 by dferjul          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		count_tokens(t_data *data)
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
}

char		*append_char_to_token(char **token, char c)
{
	int		i;
	int		len;
	char	*token_bis;

	token_bis = malloc(sizeof char*) * (ft_strlen(token)) + 1);

}

char	**lexer(char *input)
{
	char	**tab;
	int		i;
	int		j;

	tab = malloc(sizeof(char *) * (count_tokens(input) + 1));
	if (!tab)
	{
		perror("Erreur d'allocation de mémoire");
		exit(EXIT_FAILURE);
	}
	i = 0;
	j = 0;
	while (input[i])
	{
		while (input[i] && input[i] != ' ')
		{
			tab[j] = append_char_to_token(tab[j], input[i]);
			i++;
		}
		j++;
		while (input[i] == ' ')
			i++;
	}
	tab[j] = NULL;
	return (tab);
}
