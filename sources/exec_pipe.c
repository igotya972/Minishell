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

#include "../includes/minishell.h"

void	exec_simple_cmd(t_data *data, char *path, char **cmd)
{
	if (execve(path, cmd, data->envp) == -1)
		no_command(cmd[0], path, cmd, 1);
}

static void	prepare_and_exec_cmd(char **cmd, t_data *data)
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

void	child_process(t_data *data, int i, int fd[2], int fd_in)
{
	close(fd[0]);
	if (fd_in != 0)
		dup_and_close(fd_in, STDIN_FILENO);
	if (data->lexer[until_delimiteur(data->lexer, i) + 1])
		dup_and_close(fd[1], 1);
	else
		close(fd[1]);
}

void	exec_pipe(t_data *data)
{
	int		fd[2];
	int		fd_in;
	char	**delimiteur;
	int		i;
	int		status;

	i = -1;
	fd_in = 0;
	g_error = 0;
	while (data->lexer[++i] && g_error != 130)
	{
		delimiteur = cmd_until_delimiteur(data->lexer, i);
		pipe(fd);
		data->pid = ft_fork();
		child_signal(data->pid);
		if (data->pid == 0)
		{
			child_process(data, i, fd, fd_in);
			prepare_and_exec_cmd(delimiteur, data);
		}
		else
		{
			wait(&status);
			if (g_error != 130 && g_error != 131 && g_error != 127)
				g_error = WEXITSTATUS(status);
			close(fd[1]);
			if (fd_in != 0)
				close(fd_in);
			fd_in = fd[0];
			i = until_delimiteur(data->lexer, i);
		}
		ft_free_tab(delimiteur);
	}
	if (fd_in != 0)
		close(fd_in);
}

pid_t	ft_fork(void)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
	{
		perror("Erreur fork");
		exit(EXIT_FAILURE);
	}
	return (pid);
}

void	dup_and_close(int in_fd, int out_fd)
{
	if (dup2(in_fd, out_fd) == -1)
	{
		perror("dup2 failed");
		exit(EXIT_FAILURE);
	}
	if (in_fd != out_fd)
	{
		close(in_fd);
	}
}
