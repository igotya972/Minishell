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
		//printf("%s\n", data->input);
		exec_pipe(data);
		//free(data);
		//printf("pipe\n");
	}
	else
		while (data->lexer[++i])
			i = exec_cmd(data, i);
}

int	exec_cmd(t_data *data, int i)
{
	pid_t		pid;
	char		*path;
	char		**cmd;

	if (is_builtins(data->lexer[i]) == 1)
	{
		launch_builtins(data, data->lexer, i);
		i = until_delimiteur(data->lexer, i);
	}
	else
	{
		if (!data->path)
		{
			printf("%s: No such file or directory\n", data->lexer[i]);
			return (i);
		}
		cmd = cmd_until_delimiteur(data->lexer, i);
		// debug_tab(cmd);
		path = path_cmd(data->path, data->lexer[i]);
		i = until_delimiteur(data->lexer, i);
		pid = fork();
		if (pid == -1)
			ft_error("Erreur fork", data);
		else if (pid == 0 && execve(path, cmd, data->envp) == -1)
			no_command(data, path, i);
		else
			wait(NULL);
		free(path);
		free_arguments(cmd);
	}
	return (i);
}

void	no_command(t_data *data, char *path, int i)
{
	ft_putstr_fd(data->lexer[i], 2);
	ft_putstr_fd(": command not found\n", 2);
	free(path);
	exit(1);
}
