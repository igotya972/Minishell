/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afont <afont@student.42nice.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 15:33:23 by afont             #+#    #+#             */
/*   Updated: 2024/03/28 15:12:40 by afont            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	parent_process(t_data *data, t_pipe *fd, int i)
{
	close(fd->fd_pipe[1]);
	if (fd->fd_in != 0)
		close(fd->fd_in);
	fd->fd_in = fd->fd_pipe[0];
	return (until_pipe(data->lexer, i));
}

void	dup_and_close(t_data *data, int in_fd, int out_fd)
{
	if (dup2(in_fd, out_fd) == -1)
		ft_error("dup2", data);
	if (in_fd != out_fd)
		close(in_fd);
}

void	child_process(t_data *data, int i, t_pipe *fd)
{
	char	**cmd;

	close(fd->fd_pipe[0]);
	if (fd->fd_in != 0)
		dup_and_close(data, fd->fd_in, STDIN_FILENO);
	if (data->lexer[until_pipe(data->lexer, i) + 1])
		dup_and_close(data, fd->fd_pipe[1], 1);
	else
		close(fd->fd_pipe[1]);
	cmd = launch_heredoc_pipe(data, i, fd->fd_pipe);
	prepare_and_exec_cmd(cmd, data);
	end_heredoc(fd->fd_file);
}

int	until_pipe(char **str, int i)
{
	while (str[i])
	{
		if (strcmp(str[i], "|") == 0)
			return (i);
		i++;
	}
	return (i - 1);
}

void	init_pipe_data(t_pipe *fd)
{
	fd->fd_in = 0;
	fd->fd_file[0] = 0;
	fd->fd_file[1] = 0;
	fd->fd_pipe[0] = 0;
	fd->fd_pipe[1] = 0;
}
