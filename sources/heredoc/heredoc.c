/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dferjul <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 01:37:38 by dferjul           #+#    #+#             */
/*   Updated: 2024/03/25 12:52:53 by dferjul          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**launch_heredoc(t_data *data, int i, int *fd)
{
	int	type;

	*fd = 0;
	type = is_redirection(data->lexer[until_delimiteur(data->lexer, i)]);
	if (type == 1 || type == 2)
	{
		*fd = redirect_output(data, until_delimiteur(data->lexer, i));
	}
	else if (type == 3)
	{
		*fd = redirect_input_rdonly(data->lexer[until_delimiteur(data->lexer, i) + 1]);
	}
	// else if (type == 4)
	// {
	// 	*fd = redirect_input_heredoc(data->lexer[until_delimiteur(data->lexer, i) + 1]);
	// }
	debug_tab(data->lexer);
	data->lexer = del_redirect(data->lexer);
	debug_tab(data->lexer);
	// debug_tab(data->lexer);
	// ft_free_tab(cmd);
	return (cmd_until_delimiteur(data->lexer, i));
}

int	end_heredoc(int fd)
{
	if (fd)
	{
		dup2(fd, 1);
		close(fd);
	}
	return (0);
}

int	is_redirection(char *str)
{
	if (ft_strcmp(str, ">") == 0)
		return (1);
	if (ft_strcmp(str, ">>") == 0)
		return (2);
	if (ft_strcmp(str, "<") == 0)
		return (3);
	if (ft_strcmp(str, "<<") == 0)
		return (4);
	return (0);
}

char	**del_redirect(char **lexer)
{
	int		i;
	int		j;
	char	**tmp;

	i = -1;
	j = -1;
	while (lexer[++j])
	{
		if (is_redirection(lexer[j]))
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
