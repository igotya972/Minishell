/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signal.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afont <afont@student.42nice.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 04:21:34 by dferjul           #+#    #+#             */
/*   Updated: 2024/01/19 11:47:47 by afont            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	signal_manager(int signum)
{
	//printf("%d\n", signum);
	if (signum == SIGINT || signum == SIGTSTP)
	{
		// Ctrl-C, Z
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	handle_ctrld(t_data *data)
{
	if (!data->input)
	{
		printf("exit\n");
		//ft_free(data);
		exit(EXIT_SUCCESS);
	}
}
