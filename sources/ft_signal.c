/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signal.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dferjul <dferjul@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 04:21:34 by dferjul           #+#    #+#             */
/*   Updated: 2024/01/10 01:12:30 by dferjul          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include "../includes/minishell.h"

void	signal_manager(int signum)
{
	//printf("%d\n", signum);
	if (signum == SIGINT || signum == SIGTSTP)
	{
		// Ctrl-C
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