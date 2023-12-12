/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dferjul <dferjul@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 02:13:19 by dferjul           #+#    #+#             */
/*   Updated: 2023/12/12 03:34:48 by dferjul          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	exec_cmd(char *command)
{
	pid_t	pid;
	char	**argv;

	argv = {command, NULL};
	pid = fork();
	if (pid == 0)
	{
		if (execve(argv[0], argv, NULL) == -1)
		{
			perror("Erreur lors de l'exécution de la commande");
			exit(EXIT_FAILURE);
		}
	}
	else if (pid < 0)
	{
		perror("Erreur lors de la création du processus");
	}
	else
	{
		wait(NULL);
	}
}

		// Affiche le prompt
void	minishell_prompt(void)
{
	char	*input;

	while (1)
	{
		input = readline("minishell>");
		add_history(input);
		if (strcmp(input, "exit") == 0)
		{
			free(input);
			exit(EXIT_SUCCESS);
		}
		lexer(input);
		exec_cmd(input);
		free(input);
	}
}

int	main(void)
{
	minishell_prompt();
	return (0);
}
