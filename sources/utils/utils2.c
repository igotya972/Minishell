/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afont <afont@student.42nice.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 11:40:45 by afont             #+#    #+#             */
/*   Updated: 2024/03/04 12:39:41 by afont            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_parser_delimiteur(char c)
{
	char	delimiteur[3] = {'|', '>', '<'};
	int		i;

	i = -1;
	while (++i < 3)
		if (c == delimiteur[i])
			return (1);
	return (0);
}

int	nbr_parser_delimiteur(char *str)
{
	int	i;
	int	nbr;

	i = -1;
	nbr = 0;
	while (str[++i])
		if (is_parser_delimiteur(str[i]) && ft_is_in_quotes(str, i) == 0)
			nbr++;
	return (nbr);
}

int	is_exec_delimiteur(char *str)
{
	char	delimiteur[6][3] = {{"||"}, {">>"}, {"<<"}, {"|"}, {">"}, {"<"}};
	int		i;

	i = -1;
	while (++i < 6)
		if (ft_strcmp(str, delimiteur[i]) == 0)
			return (1);
	return (0);
}

char	**cmd_until_delimiteur(char **lexer, int i)
{
	int		j;
	char	**str;

	j = i;
	while (lexer[j] && !is_exec_delimiteur(lexer[j]))
		j++;
	str = malloc(sizeof(char *) * (j - i + 1));
	ft_protect_malloc(str);
	j = -1;
	while (lexer[i] && !is_exec_delimiteur(lexer[i]))
		str[++j] = ft_strdup(lexer[i++]);
	str[j + 1] = NULL;
	return (str);
}

void	debug_tab(char **tab)
{
	int	i;

	i = -1;
	printf("\nDEBUG_TAB\n");
	while (tab[++i])
		printf("tab[%d] = %s\n", i, tab[i]);
	printf("DEBUG_DONE\n\n");
}