/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afont <afont@student.42nice.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 11:40:45 by afont             #+#    #+#             */
/*   Updated: 2024/03/24 10:16:44 by afont            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

#define PD1 '|'
#define PD2 '>'
#define PD3 '<'

#define ED1 "||"
#define ED2 ">>"
#define ED3 "<<"
#define ED4 "|"
#define ED5 ">"
#define ED6 "<"

int	is_parser_delimiteur(char c)
{
	char	delimiteur[3];
	int		i;

	delimiteur[0] = PD1;
	delimiteur[1] = PD2;
	delimiteur[2] = PD3;
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
	char	*delimiteur[6];
	int		i;

	delimiteur[0] = ED1;
	delimiteur[1] = ED2;
	delimiteur[2] = ED3;
	delimiteur[3] = ED4;
	delimiteur[4] = ED5;
	delimiteur[5] = ED6;
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
	str = ft_remove_control_tab(str);
	return (str);
}

void	debug_tab(char **tab)
{
	int			i;
	int			j;
	static int	nb_debug;

	i = -1;
	printf("\nDEBUG_TAB no%d\n", nb_debug++);
	while (tab[++i])
	{
		printf("tab[%d] = ", i);
		j = -1;
		while (tab[i][++j])
		{
			if (tab[i][j] == 18)
				printf("18");
			else
				printf("%c", tab[i][j]);
		}
		printf(".\n");
	}
	printf("tab[%d] = %s.\n", i, tab[i]);
	printf("DEBUG_DONE\n\n");
}
