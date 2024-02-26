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

static void exec_cmd_from_pipe(char *cmd, t_data *data)
{
	char **args;
	char *path;

	args = ft_split(cmd, ' ');
	path = path_cmd(data->envp , args[0]);
	if (execve(path, args, data->envp) == -1)
	{
		perror("Exec failed");
		//exit(EXIT_FAILURE);
	}
}

void	exec_pipe(t_data *data)
{
	int		fd[2];
	pid_t	pid;
	char	**cmds;
	int		i;
	int 	in_fd;

	i = 0;
	cmds = ft_split(data->input, '|');
	if (cmds == NULL)
		return ;
	in_fd = open(cmds[1], O_RDONLY);
	while (cmds[i] != NULL && cmds[i + 1] != NULL)
	{
		pipe(fd);
		pid = fork();
		if (pid == -1)
			ft_error("Erreur fork");
		if (pid == 0)
		{
			dup2(fd[1], STDOUT_FILENO);
			close(fd[1]);
			dup2(in_fd, STDIN_FILENO);
			close(in_fd);
			exec_cmd_from_pipe(cmds[i], data);
			//exit(EXIT_FAILURE);
		}
		waitpid(pid, NULL, 0);
		close(fd[1]);
		in_fd = fd[0];
		i++;
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		dup2(in_fd, STDOUT_FILENO);
		close(in_fd);
		exec_cmd_from_pipe(cmds[i], data);
	}
}
