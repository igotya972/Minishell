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

	i = len_del_redirect(lexer);
	tmp = malloc(sizeof(char *) * (i + 1));
	ft_protect_malloc(tmp);
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

char	**del_redirect_pipe(char **lexer, int i_base)
{
	int		j;
	int		k;
	char	**tmp;

	k = len_del_redirect_pipe(lexer, i_base);
	tmp = malloc(sizeof(char *) * (k + 1));
	ft_protect_malloc(tmp);
	j = i_base;
	k = -1;
	while (lexer[j] && ft_strcmp(lexer[j], "|"))
	{
		if (is_redirection(lexer[j]))
			j++;
		else
			tmp[++k] = ft_strdup(lexer[j]);
		j++;
	}
	tmp[++k] = NULL;
	return (tmp);
}

int	len_del_redirect_pipe(char **lexer, int i_base)
{
	int	i;
	int	j;

	i = 0;
	j = i_base;
	while (lexer[j] && ft_strcmp(lexer[j], "|"))
	{
		i++;
		if (is_redirection(lexer[j]))
			i -= 2;
		j++;
	}
	return (i);
}

int	len_del_redirect(char **lexer)
{
	int	i;
	int	j;

	i = 0;
	j = -1;
	while (lexer[++j])
	{
		i++;
		if (is_redirection(lexer[j]))
			i -= 2;
	}
	return (i);
}
