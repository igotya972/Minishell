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

static void	exec_simple_cmd(t_data *data, char *path, char **cmd)
{
	if (execve(path, cmd, data->envp) == -1)
	{
		perror("Exec failed");
		exit(EXIT_FAILURE);
	}
}

static void prepare_and_exec_cmd(char **cmd, t_data *data)
{
	char *path;

	path = path_cmd(data->path, cmd[0]);
	exec_simple_cmd(data, path, cmd);
}

void child_process(char **cmds, int i, t_data *data, int fd[2], int fd_in)
{
	close(fd[0]);
	if (fd_in != 0)
		dup_and_close(fd_in, STDIN_FILENO); 
	if (data->lexer[until_delimiteur(data->lexer, i) + 1])
		dup_and_close(fd[1], 1);
	else
		close(fd[1]);
	prepare_and_exec_cmd(cmds, data);
}

void	exec_pipe(t_data *data)
{
	int		fd[2];
	int		fd_in;
	char	**delimiteur;
	int		i;

	i = -1;
	fd_in = 0;
	while (data->lexer[++i])
	{
		delimiteur = cmd_until_delimiteur(data->lexer, i);
		pipe(fd);
		if (ft_fork() == 0)
		{
			child_process(delimiteur, i, data, fd, fd_in);
			i = until_delimiteur(data->lexer, i);
		}
		else
		{
			wait(NULL);
			close(fd[1]);
			if (fd_in != 0)
				close(fd_in);
			fd_in = fd[0];
			i = until_delimiteur(data->lexer, i);
		}
	}
	if (fd_in != 0)
		close(fd_in);
}

pid_t	ft_fork()
{
	pid_t pid;

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
