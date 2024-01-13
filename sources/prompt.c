/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dferjul <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 02:13:19 by dferjul           #+#    #+#             */
/*   Updated: 2024/01/13 18:29:52 by dferjul          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	exec_cmd(char *command)
{
	pid_t	pid;
	char	**argv;

	argv = malloc(sizeof(char *) * 2);
	if (!argv)
	{
		perror("Erreur malloc argv");
		exit(EXIT_FAILURE);
	}
	argv[0] = command;
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
void	minishell_prompt(t_data *data)
{
	//char	*input;
	//int		signum;
	//signum = 0;
	while (1)
	{
		signal(SIGINT, &signal_manager);
		signal(SIGQUIT, SIG_IGN);
		//set_signal_action();
		data->input = readline("minishell> ");
		add_history(data->input);
		if (ft_strcmp(data->input, "exit") == 0)
		{
			free(data);
			exit(EXIT_SUCCESS);
		}
		//lexer(data);
		launch_builtins(data, data->lexer);
		//exec_cmd(input);
		free(data->input);
	}
}

int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	t_data *data;

	data = malloc(sizeof(t_data));
	if (!data)
	{
		perror("Erreur d'allocation de mémoire");
		exit(EXIT_FAILURE);
	}
	init_data(data, envp);
	minishell_prompt(data);
	return (0);
}
