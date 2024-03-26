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

int	redirect_output(t_data *data, int i)
{
	int	fd;
	int	j;
	int	len_tab;
	int	type;

	j = 0;
	len_tab = 0;
	while (data->lexer[len_tab])
		len_tab++;
	type = is_redirection(data->lexer[i]);
	i += 2;
	while ((type == 1 || type == 2) && i < len_tab && \
	(is_redirection(data->lexer[i]) == 1 || \
	is_redirection(data->lexer[i]) == 2))
	{
		j = until_delimiteur(data->lexer, j) + 1;
		fd = open_append_trunc(data->lexer[j], type);
		close(fd);
		type = is_redirection(data->lexer[i]);
		i += 2;
	}
	return (redirect_ouput2(data, type, i));
}

int	redirect_ouput2(t_data *data, int type, int i)
{
	int	fd;
	int	save;

	fd = open_append_trunc(data->lexer[i - 1], type);
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