/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_file.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afont <afont@student.42nice.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 01:07:17 by dferjul           #+#    #+#             */
/*   Updated: 2024/03/24 10:27:22 by afont            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	redirect_output_append(char *file)
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
	// int	save;

	// save = dup(1);
	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(file, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		exit(1);
		// return (-1);
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
	return (0);
}

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
		fd = open(data->lexer[j], O_CREAT | O_WRONLY | O_TRUNC, 0644);
		close(fd);
		type = is_redirection(data->lexer[i]);
		i += 2;
	}
	printf("i = %d, type = %d\n", i, type);
	return (redirect_ouput2(data, type, i));
}

int	redirect_ouput2(t_data *data, int type, int i)
{
	int	fd;
	int	save;

	if (type == 1)
		fd = open(data->lexer[i - 1], O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (type == 2)
		fd = open(data->lexer[i - 1], O_CREAT | O_WRONLY | O_APPEND, 0644);
	save = dup(1);
	dup2(fd, 1);
	close(fd);
	return (save);
}
