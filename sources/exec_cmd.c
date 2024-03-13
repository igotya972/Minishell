/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afont <afont@student.42nice.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 02:01:55 by dferjul           #+#    #+#             */
/*   Updated: 2024/03/04 17:35:19 by afont            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	launch_exec(t_data *data)
{
	int	i;

	i = -1;	
	if (ft_strchr(data->input, '|') != 0)
	{
		// signal(SIGINT, child_signal);
		//printf("%s\n", data->input);
		exec_pipe(data);
		//free(data);
		//printf("pipe\n");
	}
	else
	{
		while (data->lexer[++i])
		{
			signal(SIGINT, child_signal);
			i = exec_cmd(data, i);
			if (i == -1)
				return ;
		}
	}
}

int	exec_cmd(t_data *data, int i)
{
	pid_t		pid;
	char		*path;
	char		**cmd;

	if (is_builtins(data->lexer[i]) == 1)
		launch_builtins(data, data->lexer, i);
	else
	{
		if (!data->path)
		{
			printf("%s: No such file or directory\n", data->lexer[i]);
			return (-1);
		}
		cmd = cmd_until_delimiteur(data->lexer, i);
		path = path_cmd(data->path, data->lexer[i]);
		if (!path)
			return (no_command(data->lexer[i], path, cmd, 0));
		pid = fork();
		if (pid == -1)
			ft_error("Erreur fork", data);
		else if (pid == 0)
		{
			if (execve(path, cmd, data->envp) == -1)
				no_command(data->lexer[i], path, cmd, 1);
		}
		else
			wait(NULL);
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
	free(path);
	ft_free_tab(cmd);
	if (flag)
		exit(1);
	else
		return (-1);
}
