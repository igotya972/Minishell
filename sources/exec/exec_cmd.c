/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dferjul <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 02:01:55 by dferjul           #+#    #+#             */
/*   Updated: 2024/03/25 12:57:19 by dferjul          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	launch_exec(t_data *data)
{
	int		status;

	if (is_pipe(data->lexer))
	{
		signal(SIGINT, child_signal);
		signal(SIGQUIT, SIG_IGN);
		exec_pipe(data);
	}
	else if (data->lexer[0])
	{
		signal(SIGINT, child_signal);
		signal(SIGQUIT, child_signal);
		exec_cmd(data, 0);
	}
	while (wait(&status) > 0)
		;
	if (g_error != 130 && g_error != 131 && g_error != 127)
		g_error = WEXITSTATUS(status);
}

void	exec_cmd(t_data *data, int i)
{
	int			fd;
	char		*path;
	char		**cmd;

	g_error = 0;
	if (!data->path)
	{
		no_path(data->lexer[i]);
		return ;
	}
	path = path_cmd(data->path, data->lexer[i]);
	if (!path && !is_builtins(data->lexer[i]))
	{
		no_command(data->lexer[i], path, NULL, 0);
		return ;
	}
	if (!is_builtins(data->lexer[i]))
		data->pid = ft_fork();
	child_signal(data->pid);
	if (data->pid == 0 || is_builtins(data->lexer[i]))
	{
		cmd = launch_heredoc(data, i, &fd);
		exec_child_cmd(data, path, cmd, i);
		ft_free_tab(cmd);
		fd = end_heredoc(fd);
	}
	free(path);
}

int	no_command(char *str, char *path, char **cmd, int flag)
{
	ft_putstr_fd(str, 2);
	ft_putstr_fd(": command not found\n", 2);
	g_error = 127;
	free(path);
	if (cmd)
		ft_free_tab(cmd);
	if (flag)
		exit(127);
	else
		return (-2);
}

void	exec_child_cmd(t_data *data, char *path, char **cmd, int i)
{
	if (is_builtins(data->lexer[i]))
		launch_builtins(data, data->lexer, i);
	else
		exec_simple_cmd(data, path, cmd);
}
