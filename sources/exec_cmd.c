/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dferjul <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 02:01:55 by dferjul           #+#    #+#             */
/*   Updated: 2024/02/26 19:11:28 by dferjul          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	exec_cmd(t_data *data)
{
	pid_t	pid;
	char	*path;

	if (ft_strchr(data->input, '|') != 0)
	{
		//printf("%s\n", data->input);
		exec_pipe(data);
		//free(data);
		return;
	}
	path = path_cmd(data->envp, data->lexer[0]);
	pid = fork();
	if (pid == -1)
		ft_error("Erreur fork");
	if (pid == 0)
	{
		if (execve(path, data->lexer, data->envp) == -1)
		{
			ft_putstr_fd(data->lexer[0], 2);
			ft_putstr_fd(": command not found\n", 2);
			exit(1);
		}
	}
	else
		wait(NULL);
}
