/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_output_file.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 01:07:17 by dferjul           #+#    #+#             */
/*   Updated: 2024/03/26 02:54:53 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	redirect_output(char **lexer)
{
	int	type;
	int	save;
	int	i;

	i = -1;
	save = 0;
	while (lexer[++i])
	{
		type = is_redirection(lexer[i]);
		if ((type == 1 || type == 2))
		{
			if (is_redirection_output(lexer, i + 1))
				close(open_append_trunc(lexer[i + 1], type));
			else
				save = redirect_output2(lexer[i + 1], type);
		}
	}
	return (save);
}

int	redirect_output2(char *file, int type)
{
	int	fd;
	int	save;

	fd = open_append_trunc(file, type);
	save = dup(1);
	dup2(fd, 1);
	close(fd);
	return (save);
}

int	open_append_trunc(char *file, int type)
{
	int	fd;

	if (type == 1)
		fd = open(file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (type == 2)
		fd = open(file, O_CREAT | O_WRONLY | O_APPEND, 0644);
	return (fd);
}
