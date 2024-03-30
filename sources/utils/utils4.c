/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afont <afont@student.42nice.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 10:10:17 by afont             #+#    #+#             */
/*   Updated: 2024/03/24 10:10:44 by afont            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	delimiteur_modifier(char *tmp, char *input, int *i, int *j)
{
	if ((*i) != 0 && input[(*i) - 1] != ' ')
		tmp[++(*j)] = ' ';
	tmp[++(*j)] = input[(*i)];
	if (input[(*i) + 1] && input[(*i) + 1] == input[(*i)])
		tmp[++(*j)] = input[++(*i)];
	if (input[(*i) + 1] && input[(*i) + 1] != ' ')
		tmp[++(*j)] = ' ';
}

int	check_parse_error2(char **input, int i)
{
	if (is_redirection(input[i]) && !input[i + 1])
	{
		printf("Minishell: parse error near `\\n'\n");
		g_error = 2;
		return (1);
	}
	if (is_redirection(input[i]) && is_redirection(input[i + 1]))
	{
		printf("Minishell: parse error near `%s'\n", input[i + 1]);
		g_error = 1;
		return (1);
	}
	if (!ft_strcmp(input[i], "|") && input[i + 1] && !ft_strcmp(input[i + 1], "|"))
	{
		printf("Minishell: parse error near `|'\n");
		g_error = 2;
		return (1);
	}
	return (0);
}

char	**ft_strdup_tab(char **tab)
{
	int		i;
	char	**new_tab;

	i = 0;
	while (tab[i])
		i++;
	new_tab = malloc(sizeof(char *) * (i + 1));
	ft_protect_malloc(new_tab);
	i = -1;
	while (tab[++i])
		new_tab[i] = ft_strdup(tab[i]);
	new_tab[i] = NULL;
	return (new_tab);
}

int	nbr_redirect(char **lexer)
{
	int		i;
	int		nbr;

	i = -1;
	nbr = 0;
	while (lexer[++i])
		if (is_redirection(lexer[i]) && is_redirection(lexer[i]) != 4)
			nbr++;
	return (nbr);
}
