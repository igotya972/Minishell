/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afont <afont@student.42nice.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 15:33:23 by afont             #+#    #+#             */
/*   Updated: 2024/03/19 15:40:27 by afont            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	parent_process(int *fd_in, int fd[2], int i, t_data *data)
{
	close(fd[1]);
	if (*fd_in != 0)
		close(*fd_in);
	*fd_in = fd[0];
	return (until_delimiteur(data->lexer, i));
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
	if (data->lexer[until_delimiteur(data->lexer, i) + 1])
		dup_and_close(data, fd[1], 1);
	else
		close(fd[1]);
}
