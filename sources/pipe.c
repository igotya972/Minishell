/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dferjul <dferjul@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 05:38:29 by dferjul           #+#    #+#             */
/*   Updated: 2024/03/12 06:08:14 by dferjul          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/* int openfile(char *file, int mode)
{
	int	fd;

	if (access(file, F_OK) == 0)
		if (access(file, W_OK | R_OK) != 0)
			ft_error("Permission denied");
	if (mode == 0)
		fd = open(file, O_APPEND | O_WRONLY | O_CREAT, 0644);
	if (mode == 1)
		fd = open(file, O_TRUNC | O_WRONLY | O_CREAT, 0644);
	return (fd);
} */
