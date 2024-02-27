/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afont <afont@student.42nice.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 02:01:55 by dferjul           #+#    #+#             */
/*   Updated: 2024/02/27 17:24:40 by afont            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	exec_cmd(t_data *data)
{
	pid_t	pid;
	char	*path;
	int 	i;

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
		if (is_builtins(data->lexer[i]) == 1)
		{
			// printf("%s, %d\n", data->lexer[i], i);
			launch_builtins(data, data->lexer, i);
			i = until_limiteur(data->lexer, i);
			// printf("%s, %d\n", data->lexer[i], i);
		}
		else
		{
			path = path_cmd(data->envp, data->lexer[i]);
			pid = fork();
			if (pid == -1)
				ft_error("Erreur fork");
			if (pid == 0)
			{
				if (execve(path, data->lexer, data->envp) == -1)
				{
					ft_putstr_fd(data->lexer[i], 2);
					ft_putstr_fd(": command not found\n", 2);
					exit(1);
				}
			}
			else
				wait(NULL);
		}
		i++;
	}
}
