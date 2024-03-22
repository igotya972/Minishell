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

int	redirect_output(t_data *data, int i)
{
	int	fd;
	int	save;
	int	j;
	int len_tab;
	int	type;

	j = 0;
	len_tab = 0;
	while (data->lexer[len_tab])
		len_tab++;
	// printf("i = %d\n", i);
	// printf("q = %s\n", data->lexer[until_delimiteur(data->lexer, i)]);
	type = is_redirection(data->lexer[i]);
	i += 2;

	while ((type == 1 || type == 2) && i < len_tab && (is_redirection(data->lexer[i]) == 1 || is_redirection(data->lexer[i]) == 2))
	{
		j = until_delimiteur(data->lexer, j) + 1;
		// printf("s = %s\n", data->lexer[j]);
		fd = open(data->lexer[j], O_CREAT | O_WRONLY | O_TRUNC, 0644);
		close(fd);
		// printf("q = %s\n", data->lexer[i]);
		type = is_redirection(data->lexer[i]);
		i += 2;
	}
	// printf("j = %d, i = %d\n", j, i);
	// printf("save = %d\n", type);
	if (type == 1)
		fd = open(data->lexer[i - 1], O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (type == 2)
		fd = open(data->lexer[i - 1], O_CREAT | O_WRONLY | O_APPEND, 0644);
	save = dup(1);
	dup2(fd, 1);
	close(fd);
	return (save);
}
