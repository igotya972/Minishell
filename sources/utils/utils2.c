/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afont <afont@student.42nice.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 11:40:45 by afont             #+#    #+#             */
/*   Updated: 2024/03/01 09:03:36 by afont            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int is_parser_delimiteur(char c)
{
    char delimiteur[3] = {'|', '>', '<'};
	int	i;

	i = -1;
	while (++i < 3)
		if (c == delimiteur[i])
			return (1);
	return (0);
}

int nbr_parser_delimiteur(char *str)
{
    int i;
    int nbr;

    i = -1;
    nbr = 0;
    while (str[++i])
        if (is_parser_delimiteur(str[i]) && ft_is_in_quotes(str, i) == 0)
            nbr++;
    return (nbr);
}

int is_exec_delimiteur(char *str)
{
    char    delimiteur[6][3] = {{"||"}, {">>"}, {"<<"}, {"|"}, {">"}, {"<"}};
    int     i;

    i = -1;
    while (++i < 6)
        if (ft_strcmp(str, delimiteur[i]) == 0)
            return (1);
    return (0);
}
