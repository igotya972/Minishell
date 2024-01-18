/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dferjul <dferjul@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 02:01:55 by dferjul           #+#    #+#             */
/*   Updated: 2024/01/18 05:21:46 by dferjul          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	execute_ls(void)
{
	pid_t	pid;
	char	**argv;

	pid = fork();
	if (pid == 0)
	{
		argv = malloc(sizeof(char *) * 3);
		argv[0] = "/bin/ls";
		argv[1] = "-l";
		argv[2] = NULL;
		if (execve("/bin/ls", argv, NULL) == -1)
		{
			perror("Error exec ls");
			exit(EXIT_FAILURE);
		}
	}
	else if (pid < 0)
		perror("Error processus");
}

void	exec_cmd(char *command)
{
	pid_t	pid;
	char	**args;

	args = malloc(sizeof(char *) * 2);
	if (!args)
	{
		perror("Erreur malloc argv");
		exit(EXIT_FAILURE);
	}
	args[0] = command;
	pid = fork();
	if (pid == 0)
	{
		if (execve(args[0], args, NULL) == -1)
		{
			perror("Error exec cmd");
			exit(EXIT_FAILURE);
		}
	}
	else if (pid < 0)
		perror("Error processus");
	else
	{
		wait(NULL);
	}
}
