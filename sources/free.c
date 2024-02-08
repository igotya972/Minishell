/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afont <afont@student.42nice.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 03:03:07 by dferjul           #+#    #+#             */
/*   Updated: 2024/02/08 14:45:25 by afont            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_arguments(char **args)
{
	int	i;

	i = 0;
	while (args[i] != NULL)
	{
		free(args[i]);
		i++;
	}
	free(args);
}

void	ft_free(t_data *data)
{
	int	i;

	i = -1;
	if (data->export[0].key)
	{
		while (data->export[++i].key)
		{
			free(data->export[i].key);
			free(data->export[i].value);
			free(data->export[i].export_str);
		}
		free(data->export);
	}
	if (data->input)
		free(data->input);
	if (data->envp[0])
	{
		i = -1;
		while (data->envp[++i])
			free(data->envp[i]);
		free(data->envp);
	}
	if (data->old_pwd)
		free(data->old_pwd);
	free(data);
	exit(EXIT_SUCCESS);
}

void	ft_free_input_lexer(t_data *data)
{
	int	i;

	i = -1;
	if (data->lexer)
	{
		while (data->lexer[++i])
			free(data->lexer[i]);
		free(data->lexer);
	}
	free(data->input);
}
