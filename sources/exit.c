/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dferjul <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 03:25:56 by dferjul           #+#    #+#             */
/*   Updated: 2024/02/11 03:25:56 by dferjul          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_exit(t_data *data)
{
	ft_free(data);
	exit(EXIT_SUCCESS);
}

void	ft_error(char *str)
{
	perror(str);
	exit(EXIT_FAILURE);
}