/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afont <afont@student.42nice.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 02:01:55 by dferjul           #+#    #+#             */
/*   Updated: 2024/02/09 09:31:15 by afont            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_ls(t_data *data, char **inputs, int i)
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
		argv = ft_ls2(inputs[i + 1]);
		if (execve("/bin/ls", argv, NULL) == -1)
		{
			perror("Error exec ls");
			free(argv);
			ft_free(data);
		}
		free(argv);
	}
	else
		waitpid(pid, NULL, 0);
}

char	**ft_ls2(char *input)
{
	char	**tmp_argv;

	tmp_argv = malloc(sizeof(char *) * 3);
	if (!tmp_argv)
	{
		perror("Error malloc");
		exit(EXIT_FAILURE);
	}
	tmp_argv[0] = "/bin/ls";
	tmp_argv[1] = input;
	tmp_argv[2] = NULL;
	return (tmp_argv);
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
