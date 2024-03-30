/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils5.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afont <afont@student.42nice.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 11:30:41 by afont             #+#    #+#             */
/*   Updated: 2024/03/28 11:30:42 by afont            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_redirection_input(char **lexer, int i)
{
	while (lexer[i])
	{
		if (ft_strcmp(lexer[i], "<") == 0 || ft_strcmp(lexer[i], "<<") == 0)
			return (1);
		i++;
	}
	return (0);
}

int	is_redirection_output(char **lexer, int i)
{
	while (lexer[i])
	{
		if (ft_strcmp(lexer[i], ">") == 0 || ft_strcmp(lexer[i], ">>") == 0)
			return (1);
		i++;
	}
	return (0);
}

int	is_builtins_last(char **str)
{
	int	i;
	int	j;

	i = -1;
	j = 0;
	while (str[++i])
		if (!strcmp(str[i], "|"))
			j = i;
	return (is_builtins(str[j + 1]));
}

void	wait_pipe(t_data *data)
{
	int	status;

	while (wait(&status) > 0)
		;
	if (!is_builtins_last(data->lexer) && g_error != \
	130 && g_error != 131 && g_error != 127)
		g_error = WEXITSTATUS(status);
}

void	wait_exec(t_data *data)
{
	int	status;

	if (!is_builtins(data->lexer[0]))
	{
		while (wait(&status) > 0)
			;
		if (g_error != 130 && g_error != 131 && g_error != 127)
			g_error = WEXITSTATUS(status);
	}
}
