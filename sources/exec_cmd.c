/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dferjul <dferjul@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 02:01:55 by dferjul           #+#    #+#             */
/*   Updated: 2024/01/18 06:02:42 by dferjul          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	execute_ls(void)
{
	pid_t	pid;
	char	**argv;

	pid = fork();
	if (pid == -1)
	{
		perror("Error fork");
		exit(EXIT_FAILURE);
	}
	if (pid == 0)
	{
		argv = malloc(sizeof(char *) * 3);
		if (!argv)
		{
			perror("Error malloc");
			exit(EXIT_FAILURE);
		}
		argv[0] = "/bin/ls";
		argv[1] = "-l";
		argv[2] = NULL;
		if (execve("/bin/ls", argv, NULL) == -1)
		{
			perror("Error exec ls");
			free(argv);
			exit(EXIT_FAILURE);
		}
	}
	else
		waitpid(pid, NULL, 0);
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
	if (pid == -1)
	{
		perror("Erreur fork");
		exit(EXIT_FAILURE);
	}
	if (pid == 0)
	{
		if (execve(args[0], args, NULL) == -1)
		{
			perror("Error exec cmd");
			exit(EXIT_FAILURE);
		}
	}
	else
		wait(NULL);
}
