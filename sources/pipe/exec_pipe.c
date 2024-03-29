/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dferjul <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 18:12:43 by dferjul           #+#    #+#             */
/*   Updated: 2024/02/26 18:12:43 by dferjul          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	exec_simple_cmd(t_data *data, char *path, char **cmd)
{
	if (execve(path, cmd, data->envp) == -1)
		no_command(cmd[0], path, cmd, 1);
}

void	prepare_and_exec_cmd(char **cmd, t_data *data)
{
	char	*path;

	if (is_builtins(cmd[0]))
	{
		launch_builtins(data, cmd, 0);
		exit(0);
	}
	else
	{
		path = path_cmd(data->path, cmd[0]);
		exec_simple_cmd(data, path, cmd);
	}
}

void	exec_pipe(t_data *data)
{
	int		fd_pipe[2];
	int 	file_fd[2];
	int		fd_in;
	int		i;
	char	**delimiteur;
	char	**cmd;

	file_fd[0] = 0;
	file_fd[1] = 0;
	i = -1;
	fd_in = 0;
	g_error = 0;
	while (data->lexer[++i] && g_error != 130)
	{
		delimiteur = cmd_until_delimiteur(data->lexer, i);
		if (!data->path && !is_builtins(delimiteur[0]))
		{
			no_path(delimiteur[0]);
			i = until_delimiteur(data->lexer, i);
		}
		else
		{
			pipe(fd_pipe);
			data->pid = ft_fork(data);
			child_signal(data->pid);
			if (data->pid == 0)
			{
				child_process(data, i, fd_pipe, fd_in);
				cmd = launch_heredoc_pipe(data, i, file_fd);
				prepare_and_exec_cmd(cmd, data);
				end_heredoc(file_fd);
			}
			else
				i = parent_process(&fd_in, fd_pipe, i, data);
		}
		ft_free_tab(delimiteur);
	}
	if (fd_in != 0)
		close(fd_in);
}

pid_t	ft_fork(t_data *data)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		ft_error("fork", data);
	return (pid);
}
