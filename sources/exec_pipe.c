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

static void	exec_cmd_from_pipe(char **cmd, t_data *data, int i)
{
	char	**args;
	char	*path;

	args = ft_split(cmd[i], ' ');
	//printf("args[i] = %s\n", args[i]);
	path = path_cmd(data->path, args[0]);
	if (execve(path, args, data->envp) == -1)
	{
		perror("Exec failed");
		exit(EXIT_FAILURE);
	}
}

void	exec_pipe(t_data *data)
{
	int		fd[2];
	int		fd_in;
	pid_t	pid;
	char	**cmds;
	int		i;

	i = 0;
	fd_in = 0;
	cmds = ft_split(data->input, '|');
	if (cmds == NULL)
		return ;
	while (cmds[i])
	{
		pipe(fd);
		pid = fork();
		if (pid == -1)
		{
			perror("Erreur fork");
			exit(EXIT_FAILURE);
		}
		if (pid == 0)
		{
			close(fd[0]);
			if (fd_in != 0)
			{
				dup2(fd_in, 0);
				close(fd_in);
			}
			if (cmds[i + 1] != NULL)
				dup2(fd[1], 1);
			close(fd[1]);
			exec_cmd_from_pipe(cmds, data, i);
			exit(EXIT_FAILURE);
		}
		else
		{
			waitpid(pid, NULL, 0);
			close(fd[1]);
			if (fd_in != 0)
				close(fd_in);
			fd_in = fd[0];
			i++;
		}
	}
	if (fd_in != 0)
		close(fd_in);
}
