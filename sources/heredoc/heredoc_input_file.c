/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_input_file.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 01:21:30 by marvin            #+#    #+#             */
/*   Updated: 2024/03/26 01:21:30 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	redirect_input_rdonly(char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(file, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		exit(1);
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
	return (0);
}

int	redirect_input_heredoc(char *delimiter)
{
	int		pipe_fd[2];
	pid_t	pid;
	char	*line;
	size_t	len;

	len = 0;
	line = NULL;
	if (pipe(pipe_fd) == -1)
	{
		perror("pipe");
		return (-1);
	}
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		return (-1);
	}
	if (pid == 0)
	{
		close(pipe_fd[0]);
		while (getline(&line, &len, stdin) != -1)
		{
			if (strncmp(line, delimiter, strlen(delimiter)) == 0)
			{
				break ;
			}
			write(pipe_fd[1], line, strlen(line));
		}
		free(line);
		close(pipe_fd[1]);
		exit(EXIT_SUCCESS);
	}
	else
	{
		close(pipe_fd[1]);
		dup2(pipe_fd[0], STDIN_FILENO);
		close(pipe_fd[0]);
		wait(NULL);
	}
	return (0);
}
