/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afont <afont@student.42nice.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 02:13:19 by dferjul           #+#    #+#             */
/*   Updated: 2024/03/25 10:54:21 by afont            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	minishell_prompt(t_data *data)
{
	char	*prompt;

	while (1)
	{
		signal(SIGINT, &signal_manager);
		signal(SIGQUIT, SIG_IGN);
		prompt = ft_init_prompt(data);
		data->input = readline(prompt);
		free(prompt);
		handle_ctrld(data);
		ft_add_history(data, data->input);
		lexer(data);
		if (data->input[0] && !check_parse_error(data->lexer))
			launch_exec(data);
		ft_free_tab(data->lexer);
		free(data->input);
	}
}
