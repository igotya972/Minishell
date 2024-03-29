/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_pipe2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afont <afont@student.42nice.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 14:23:58 by afont             #+#    #+#             */
/*   Updated: 2024/03/29 14:23:59 by afont            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_pipe_path(t_data *data, int *i)
{
	if (!data->path && !is_builtins(data->lexer[*i]))
	{
		no_path(data->lexer[*i]);
		*i = until_pipe(data->lexer, *i);
		return (0);
	}
	else
		return (1);
}
