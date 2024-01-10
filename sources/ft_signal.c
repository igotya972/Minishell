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
	
	if (signum == SIGINT)
	{
		// Ctrl-C
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		//minishell_prompt();
	}
	else if (signum == SIGCHLD)
	{
		// Ctrl-D
		//free(input);
		exit(EXIT_SUCCESS);
	}
	else if (signum == SIGQUIT)
	{
		// Ctrl-\ : Ne fait rien
		minishell_prompt();
	}
}
