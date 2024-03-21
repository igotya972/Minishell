/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dferjul <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 02:01:55 by dferjul           #+#    #+#             */
/*   Updated: 2024/03/21 14:04:34 by dferjul          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	launch_exec(t_data *data)
{
	int		i;
	int		status;

	i = -1;
	if (is_pipe(data->lexer))
	{
		signal(SIGINT, child_signal);
		signal(SIGQUIT, SIG_IGN);
		exec_pipe(data);
	}
	else
	{
		while (i != -2 && data->lexer[++i])
		{
			signal(SIGINT, child_signal);
			signal(SIGQUIT, child_signal);
			i = exec_cmd(data, i);
		}
	}
	while (wait(&status) > 0)
		;
	if (g_error != 130 && g_error != 131 && g_error != 127)
		g_error = WEXITSTATUS(status);
}

int	exec_cmd(t_data *data, int i)
{ 
	int			fd;
	char		*path;
	char		**cmd;

	if (is_builtins(data->lexer[i]))
		launch_builtins(data, data->lexer, i);
	else
	{
		g_error = 0;
		if (!data->path)
			return (no_path(data->lexer[i]));
		cmd = cmd_until_delimiteur(data->lexer, i);
		path = path_cmd(data->path, data->lexer[i]);
		if (!path)
			return (no_command(data->lexer[i], path, cmd, 0));
		data->pid = ft_fork();
		child_signal(data->pid);
		if (is_redirection(data->lexer[until_delimiteur(data->lexer, i)]) == 1)
		{
			fd = create_file();
		}
		if (is_redirection(data->lexer[until_delimiteur(data->lexer, i)]) == 2)
		{
			fd = redirect_output_append(data->input);
		}
		if (is_redirection(data->lexer[until_delimiteur(data->lexer, i)]) == 3)
		{
			fd = redirect_input_rdonly(data->input);
		}
			// if (is_redirection(data->input) == 2)
			// {
			// 	fd = redirect_output_append(data->input);
			// }
			// if (is_redirection(data->input) == 3)
			// {
				
			// }
			// if (is_redirection(data->input) == 4)
			// {
				
			// }
		//}
		if (data->pid == 0)
			exec_simple_cmd(data, path, cmd);
		if (fd)
		{
			dup2(fd, 1);
			close(fd);
			fd = 0;
		}
		free(path);
		ft_free_tab(cmd);
	}
	i = until_delimiteur(data->lexer, i);
	return (i);
}

int	no_command(char *str, char *path, char **cmd, int flag)
{
	ft_putstr_fd(str, 2);
	ft_putstr_fd(": command not found\n", 2);
	g_error = 127;
	free(path);
	ft_free_tab(cmd);
	if (flag)
		exit(127);
	else
		return (-2);
}
