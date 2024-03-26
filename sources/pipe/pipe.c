/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dferjul <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 04:54:38 by dferjul           #+#    #+#             */
/*   Updated: 2024/03/26 04:54:38 by dferjul          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/* void exec_pipe_bis(t_data *data, char **delimiter, int *fd, int fd_in, int i)
{
	if (!data->path && !is_builtins(delimiter[0]))
	{
		no_path(delimiter[0]);
		i = until_delimiteur(data->lexer, i);
	}
	else
	{
		pipe(fd);
		data->pid = ft_fork();
		child_signal(data->pid);
		if (data->pid == 0)
		{
			child_process(data, i, fd, fd_in);
			prepare_and_exec_cmd(delimiter, data);
			exit(EXIT_FAILURE);
		}
		else
			i = parent_process(&fd_in, fd, i, data);
	}
} */

/* void exec_pipe(t_data *data)
{
	int		fd[2];
	int		fd_in;
	char	**delimiteur;
	int		i;

	i = -1;
	fd_in = 0;
	g_error = 0;
	while (data->lexer[++i] && g_error != 130)
	{
		delimiter = cmd_until_delimiteur(data->lexer, i);
		execute_command(data, delimiter, fd, fd_in, i);
		ft_free_tab(delimiter);
	}
	if (fd_in != 0)
		close(fd_in);
} */
