/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dferjul <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 02:01:55 by dferjul           #+#    #+#             */
/*   Updated: 2024/02/13 03:16:42 by dferjul          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	exec_cmd(t_data *data)
{
	pid_t	pid;
	char	**args;
	char	*path;

	args = ft_split(data->input, ' ');
	if (args == NULL)
		return ;
	path = path_cmd(data->envp, args[0]);
	pid = fork();
	if (pid == -1)
		ft_error("Erreur fork");
	if (pid == 0)
	{
		if (execve(path, args, NULL) == -1)
		{
			ft_putstr_fd(args[0], 2);
			ft_putstr_fd(": command not found\n", 2);
			exit(1);
		}
	}
	else
		wait(NULL);
}
