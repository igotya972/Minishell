/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del_redirect.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afont <afont@student.42nice.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 11:30:35 by afont             #+#    #+#             */
/*   Updated: 2024/03/28 11:30:36 by afont            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**del_redirect(char **lexer)
{
	int		i;
	int		j;
	char	**tmp;

	i = -1;
	j = -1;
	while (lexer[++j])
	{
		if (is_redirection(lexer[j]) == 1 || is_redirection(lexer[j]) == 2)
			i -= 1;
		i++;
	}
	tmp = malloc(sizeof(char *) * (i + 2));
	i = -1;
	j = -1;
	while (lexer[++i])
	{
		if (is_redirection(lexer[i]))
			i++;
		else
			tmp[++j] = ft_strdup(lexer[i]);
	}
	tmp[++j] = NULL;
	ft_free_tab(lexer);
	return (tmp);
}
