/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_file.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dferjul <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 01:07:17 by dferjul           #+#    #+#             */
/*   Updated: 2024/03/21 14:04:08 by dferjul          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int redirect_output_append(char *file)
{
	int	fd;
	int	save;

	save = dup(1);
	fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (save);
}

int	redirect_input_rdonly(char *file)
{
	int	fd;
	int	save;

	save = dup(1);
	fd = open(file, O_RDONLY);
	dup2(fd, STDIN_FILENO);
	close(fd);
	return (save);
}

int	redirect_output_trunc(t_data *data, int i)
{
	int	fd;
	int save;

	while (is_redirection(data->lexer[until_delimiteur(data->lexer, ++i)]) == 1)
	{
		fd = open(data->lexer[until_delimiteur(data->lexer, i) - 1], O_CREAT | O_WRONLY | O_TRUNC, 0644);
		close(fd);
	}
	fd = open(data->lexer[i], O_CREAT | O_WRONLY | O_TRUNC, 0644);
	save = dup(1);
	dup2(fd, 1);
	close(fd);
	return (save);
}
