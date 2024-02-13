/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dferjul <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 02:13:19 by dferjul           #+#    #+#             */
/*   Updated: 2024/02/13 15:39:45 by dferjul          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
		lexer(data);
		// lexer_temporaire(data);
		exec_cmd(data);
		launch_builtins(data, data->lexer);
		ft_free_input_lexer(data);
	}
}
