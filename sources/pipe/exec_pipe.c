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
	int		i;
	t_pipe	*fd;

	fd = malloc(sizeof(t_pipe));
	ft_protect_malloc(fd);
	init_pipe_data(fd);
	i = -1;
	g_error = 0;
	while (data->lexer[++i] && g_error != 130)
	{
		if (check_pipe_path(data, &i))
		{
			pipe(fd->fd_pipe);
			data->pid = ft_fork(data);
			child_signal(data->pid);
			if (data->pid == 0)
				child_process(data, i, fd);
			else
				i = parent_process(data, fd, i);
		}
	}
	if (fd->fd_in)
		close(fd->fd_in);
	free(fd);
}

pid_t	ft_fork(t_data *data)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		ft_error("fork", data);
	return (pid);
}
