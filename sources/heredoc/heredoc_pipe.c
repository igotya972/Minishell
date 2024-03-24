/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afont <afont@student.42nice.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 10:19:58 by afont             #+#    #+#             */
/*   Updated: 2024/03/24 10:20:06 by afont            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**launch_heredoc_pipe(t_data *data, int i, int *fd)
{
	int	type;

	*fd = 0;
	type = is_redirection(data->lexer[until_delimiteur(data->lexer, i)]);
	if (type == 1 || type == 2)
	{
		*fd = redirect_output(data, until_delimiteur(data->lexer, i));
	}
	else if (type == 3)
	{
		*fd = redirect_input_rdonly(data->lexer[until_delimiteur(data->lexer, i) + 1]);
	}
	// else if (type == 4)
	// {
	// 	*fd = redirect_input_heredoc(data->lexer[until_delimiteur(data->lexer, i) + 1]);
	// }

	data->lexer = del_redirect(data->lexer);
	// debug_tab(data->lexer);
	// ft_free_tab(cmd);
	return (cmd_until_delimiteur(data->lexer, i));
}
