/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dferjul <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 01:56:12 by dferjul           #+#    #+#             */
/*   Updated: 2024/02/11 01:56:12 by dferjul          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	child_process(int *fd, char **argv, char **env)
{
	int		fd_inf;
	char	*path;
	char	**arg;

	fd_inf = open(argv[1], O_RDONLY);
	if (fd_inf < 0)
		perror(argv[1]);
	if (access(argv[1], F_OK) != 0)
		ft_error("No such file or directory error\n");
	if (access(argv[1], R_OK) != 0)
		ft_error("Permission denied error\n");
	(void) fd;
	dup2(fd[1], STDOUT_FILENO);
	close(fd[1]);
	dup2(fd_inf, STDIN_FILENO);
	close(fd_inf);
	arg = ft_split(argv[2], ' ');
	path = path_cmd(env, arg[0]);
	execve(path, arg, env);
	ft_error("Exec failed");
	return (0);
}

int	parent_process(int *fd, char **argv, char **env)
{
	int		fd_out;
	char	*path;
	char	**arg;

	fd_out = open(argv[4], O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (fd_out < 0)
		perror(argv[4]);
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
	dup2(fd_out, STDOUT_FILENO);
	close(fd_out);
	arg = ft_split(argv[3], ' ');
	path = path_cmd(env, arg[0]);
	execve(path, arg, env);
	ft_error("Exec failed");
	return (0);
}
