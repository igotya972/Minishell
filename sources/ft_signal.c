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
	(void)signum;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	g_error = 130;
}

void	handle_ctrld(t_data *data)
{
	if (!data->input)
	{
		// if (data->pid)
		// {
		// 	printf("ctrlD %d\n", data->pid);
		// 	kill(data->pid, SIGKILL);
		// 	data->pid = 0;
		// }
		printf("exit\n");
		ft_free(data);
		exit(0);
	}
}

void	child_signal(int signum)
{
	static int	pid;

	if (signum == SIGINT)
	{
		write(1, "\n", 1);
		if (pid)
			kill(pid, SIGKILL);
		pid = 0;
		g_error = 130;
	}
	else if (signum == SIGQUIT)
	{
		write(1, "\n", 1);
		g_error = 131;
	}
	else if (pid == 0)
		pid = signum;
}
