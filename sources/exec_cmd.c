/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afont <afont@student.42nice.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 02:01:55 by dferjul           #+#    #+#             */
/*   Updated: 2024/03/01 16:11:41 by afont            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	exec_cmd(t_data *data)
{
	pid_t		pid;
	char		*path;
	int 		i;

	i = 0;	
	if (ft_strchr(data->input, '|') != 0)
	{
		//printf("%s\n", data->input);
		exec_pipe(data);
		//free(data);
		return;
	}
	while (data->lexer[i])
	{
		if (i == -1)
			return ;
		if (is_builtins(data->lexer[i]) == 1)
		{
			launch_builtins(data, data->lexer, i);
			i = until_limiteur(data->lexer, i);
		}
		else
		{
			if (!data->path)
			{
				printf("%s: No such file or directory\n", data->lexer[i]);
				return ;
			}
			path = path_cmd(data->path, data->lexer[i]);
			pid = fork();
			if (pid == -1)
				ft_error("Erreur fork");
			else if (pid == 0 && execve(path, data->lexer, data->envp) == -1)
			{
				no_command(data, path, i);
				// return ;
			}
			else
				wait(NULL);
			free(path);
		}
		i++;
	}
}

void	no_command(t_data *data, char *path, int i)
{
	ft_putstr_fd(data->lexer[i], 2);
	ft_putstr_fd(": command not found\n", 2);
	free(path);
	exit(1);
	// return ;
}
