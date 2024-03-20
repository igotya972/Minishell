/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dferjul <dferjul@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 01:37:38 by dferjul           #+#    #+#             */
/*   Updated: 2024/03/20 18:11:05 by dferjul          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// void    read_heredoc(t_cmd *cmd)
// {
	
// }

// void    create_fd(int fd)
// {
//     fd = open("/")  
// }

int    is_redirection(char *str)
{
	if (ft_strcmp(str, ">") == 0)
		return (1);
	if (ft_strcmp(str, ">>") == 0)
		return (2);
	if (ft_strcmp(str, "<") == 0)
		return (3);
	if (ft_strcmp(str, "<<") == 0)
		return (4);
	return (0);
}

int	create_file()
{
	int	fd;
	int save;

	save = dup(1);
	fd = open("heredoc", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	dup2(fd, 1);
	close(fd);
	return (save);
}

int	dup_and_truc(int fd)
{
	int	result;
	close(1);
	result = dup2(fd, 1);
	
	return result;
}

