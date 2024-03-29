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

int	parent_process(int *fd_in, int fd[2], int i, t_data *data)
{
	close(fd[1]);
	if (*fd_in != 0)
		close(*fd_in);
	*fd_in = fd[0];
	return (until_pipe(data->lexer, i));
}

void	dup_and_close(t_data *data, int in_fd, int out_fd)
{
	if (dup2(in_fd, out_fd) == -1)
		ft_error("dup2", data);
	if (in_fd != out_fd)
		close(in_fd);
}

void	child_process(t_data *data, int i, int fd[2], int fd_in)
{
	close(fd[0]);
	if (fd_in != 0)
		dup_and_close(data, fd_in, STDIN_FILENO);
	if (data->lexer[until_pipe(data->lexer, i) + 1])
		dup_and_close(data, fd[1], 1);
	else
		close(fd[1]);
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