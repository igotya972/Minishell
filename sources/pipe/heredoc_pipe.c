/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afont <afont@student.42nice.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 14:23:55 by afont             #+#    #+#             */
/*   Updated: 2024/03/29 14:23:56 by afont            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**launch_heredoc_pipe(t_data *data, int i, int file_fd[2])
{
	if (is_redirection_input_pipe(data->lexer, i))
	{
		file_fd[0] = redirect_input_pipe(data, data->lexer, i);
	}
	if (is_redirection_output_pipe(data->lexer, i))
	{
		file_fd[1] = redirect_output_pipe(data->lexer, i);
	}
	return (del_redirect_pipe(data->lexer, i));
}

int	is_redirection_input_pipe(char **lexer, int i)
{
	while (lexer[i])
	{
		if (!ft_strcmp(lexer[i], "|"))
			return (0);
		if (!ft_strcmp(lexer[i], "<") || !ft_strcmp(lexer[i], "<<"))
			return (1);
		i++;
	}
	return (0);
}

int	is_redirection_output_pipe(char **lexer, int i)
{
	while (lexer[i])
	{
		if (!ft_strcmp(lexer[i], "|"))
			return (0);
		if (!ft_strcmp(lexer[i], ">") || !ft_strcmp(lexer[i], ">>"))
			return (1);
		i++;
	}
	return (0);
}

int	redirect_input_pipe(t_data *data, char **lexer, int i)
{
	int		type;
	int		save;

	save = 0;
	while (lexer[i] && ft_strcmp(lexer[i], "|"))
	{
		type = is_redirection(lexer[i]);
		if (type == 3 && !is_redirection_input_pipe(lexer, i + 1))
		{
			save = redirect_input_rdonly(data, lexer[i + 1]);
		}
		else if (type == 4)
		{
			signal(SIGINT, child_signal_heredoc);
			signal(SIGQUIT, SIG_IGN);
			if (is_redirection_input_pipe(lexer, i + 1))
				fake_heredoc(lexer[i + 1]);
			else
				redirect_input_heredoc(data, lexer[i + 1]);
		}
		i++;
	}
	return (save);
}

int	redirect_output_pipe(char **lexer, int i)
{
	int	type;
	int	save;

	save = 0;
	while (lexer[i] && ft_strcmp(lexer[i], "|"))
	{
		type = is_redirection(lexer[i]);
		if ((type == 1 || type == 2))
		{
			if (is_redirection_output_pipe(lexer, i + 1))
				close(open_append_trunc(lexer[i + 1], type));
			else
				save = redirect_output2(lexer[i + 1], type);
		}
		i++;
	}
	return (save);
}
