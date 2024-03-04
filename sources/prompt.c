/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afont <afont@student.42nice.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 02:13:19 by dferjul           #+#    #+#             */
/*   Updated: 2024/03/04 16:42:57 by afont            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	minishell_prompt(t_data *data)
{
	char	*prompt;
	// int i;

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
		// i = -1;
		// while (data->lexer[++i])
		// 	printf("%s\n", data->lexer[i]);
		// printf("--------------------------------------------\n");
		launch_exec(data);
		ft_free_input_lexer(data);
	}
}
