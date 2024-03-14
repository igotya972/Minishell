/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signal.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afont <afont@student.42nice.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 04:21:34 by dferjul           #+#    #+#             */
/*   Updated: 2024/03/04 17:51:46 by afont            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	signal_manager(int signum)
{
	if (signum == SIGINT || signum == SIGTSTP)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		g_error = 130;
	}
}

void	handle_ctrld(t_data *data)
{
	if (!data->input)
	{
		printf("exit\n");
		ft_free(data);
		exit(0);
	}
}

void	child_signal(int signum)
{
	if (signum == SIGINT)
	{
		write(1, "\n", 1);
		g_error = 130;
		// exit(130);
		// kill(getpid(), SIGKILL);
	}
	if (signum == SIGQUIT)
	{
		write(1, "\n", 1);
		g_error = 131;
	}
}
