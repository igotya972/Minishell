/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dferjul <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 01:37:38 by dferjul           #+#    #+#             */
/*   Updated: 2024/03/26 04:53:17 by dferjul          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**launch_heredoc(t_data *data, int i, int fd[2])
{
	if (is_redirection_input(data->lexer, 0))
	{
		fd[0] = redirect_input(data, data->lexer);
	}
	if (is_redirection_output(data->lexer, 0))
	{
		fd[1] = redirect_output(data->lexer);
	}
	data->lexer = del_redirect(data->lexer);
	return (cmd_until_delimiteur(data->lexer, i));
}

void	end_heredoc(int fd[2])
{
	if (fd[0] && fd[0] != -1)
	{
		dup2(fd[0], 1);
		close(fd[0]);
	}
	if (fd[1] && fd[1] != -1)
	{
		dup2(fd[1], 1);
		close(fd[1]);
	}
	fd[0] = 0;
	fd[1] = 0;
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
