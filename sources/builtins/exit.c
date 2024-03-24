/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dferjul <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 03:25:56 by dferjul           #+#    #+#             */
/*   Updated: 2024/02/11 03:25:56 by dferjul          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_exit(t_data *data, int i)
{
	int	status;

	if (data->lexer[i + 1] && !is_exec_delimiteur(data->lexer[i + 1]) && \
	data->lexer[i + 2] && !is_exec_delimiteur(data->lexer[i + 2]))
	{
		printf("exit: too many arguments\n");
		exit(1);
	}
	if (data->lexer[i + 1] && !is_exec_delimiteur(data->lexer[i + 1]))
	{
		status = ft_atoi_simple(data->lexer[i + 1]);
		ft_free(data);
		if (status != -1)
			exit(status);
		else
		{
			printf("exit: %s: numeric argument required\n", data->lexer[i + 1]);
			exit(2);
		}
	}
	ft_free(data);
	exit(0);
}

void	ft_error(char *str, t_data *data)
{
	g_error = 1;
	perror(str);
	ft_free(data);
	exit(1);
}
