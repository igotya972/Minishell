/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afont <afont@student.42nice.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 02:13:19 by dferjul           #+#    #+#             */
/*   Updated: 2024/02/08 10:15:42 by afont            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

		// Affiche le prompt
void	minishell_prompt(t_data *data)
{
	char	*prompt;

	while (1)
	{
		signal(SIGINT, &signal_manager);
		signal(SIGTSTP, &signal_manager);
		signal(SIGQUIT, SIG_IGN);
		prompt = ft_init_prompt();
		data->input = readline(prompt);
		free(prompt);
		handle_ctrld(data);
		add_history(data->input);
		// lexer(data);
		lexer_temporaire(data);
		launch_builtins(data, data->lexer);
		// exec_cmd(data->input);
		ft_free_input_lexer(data);
	}
}
