/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_input_file.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dferjul <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 04:50:51 by dferjul           #+#    #+#             */
/*   Updated: 2024/03/26 04:50:51 by dferjul          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	redirect_input(t_data *data, char **lexer)
{
	int	i;
	int	type;
	int	save;

	save = 0;
	i = -1;
	while (lexer[++i])
	{
		type = is_redirection(lexer[i]);
		if (type == 3 && !is_redirection_input(lexer, i + 1))
		{
			save = redirect_input_rdonly(data, lexer[i + 1]);
		}
		else if (type == 4)
		{
			signal(SIGINT, child_signal_heredoc);
			signal(SIGQUIT, SIG_IGN);
			if (is_redirection_input(lexer, i + 1))
				fake_heredoc(lexer[i + 1]);
			else
				redirect_input_heredoc(data, lexer[i + 1]);
		}
	}
	return (save);
}

int	redirect_input_rdonly(t_data *data, char *file)
{
	int	fd;
	int	save;

	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(file, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		if (!is_builtins(data->lexer[0]))
			exit(1);
		else
			return (-1);
	}
	if (is_builtins(data->lexer[0]))
		return (0);
	save = dup(0);
	dup2(fd, 0);
	close(fd);
	return (save);
}

void	read_and_write_to_pipe(int pipe_write_end, char *delimiter)
{
	char	*line;

	while (1)
	{
		line = readline("heredoc> ");
		if (!line || ft_strcmp(line, delimiter) == 0)
		{
			free(line);
			break ;
		}
		write(pipe_write_end, line, ft_strlen(line));
		write(pipe_write_end, "\n", 1);
		free(line);
	}
}

void	redirect_input_heredoc(t_data *data, char *delimiter)
{
	int		pipe_fd[2];
	pid_t	pid;

	pipe(pipe_fd);
	pid = ft_fork(data);
	if (pid == 0)
	{
		close(pipe_fd[0]);
		read_and_write_to_pipe(pipe_fd[1], delimiter);
		close(pipe_fd[1]);
		exit(EXIT_SUCCESS);
	}
	else
	{
		close(pipe_fd[1]);
		dup2(pipe_fd[0], 0);
		close(pipe_fd[0]);
		wait(NULL);
	}
}

void	fake_heredoc(char *delimiter)
{
	char	*line;

	while (1)
	{
		line = readline("heredoc> ");
		if (!line || ft_strcmp(line, delimiter) == 0)
		{
			free(line);
			break ;
		}
		free(line);
	}
}
