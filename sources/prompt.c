/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afont <afont@student.42nice.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 02:13:19 by dferjul           #+#    #+#             */
/*   Updated: 2024/01/19 11:24:48 by afont            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

		// Affiche le prompt
void	minishell_prompt(t_data *data)
{
	while (1)
	{
		signal(SIGINT, &signal_manager);
		signal(SIGTSTP, &signal_manager);
		signal(SIGQUIT, SIG_IGN);
		data->input = readline("\033[0;34mminishell>\033[0;0m ");
		handle_ctrld(data);
		add_history(data->input);
		if (ft_strcmp(data->input, "exit") == 0)
		{
			// ft_free(data);
			exit(EXIT_SUCCESS);
		}
		if (ft_strcmp(data->input, "ls") == 0)
			execute_ls();
		//lexer(data);
		lexer_temporaire(data);
		launch_builtins(data, data->lexer);
		//exec_cmd(data->input);
		free(data->input);
	}
}