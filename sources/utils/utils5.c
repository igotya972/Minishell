/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils5.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afont <afont@student.42nice.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 11:30:41 by afont             #+#    #+#             */
/*   Updated: 2024/03/28 11:30:42 by afont            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_redirection_input(char **lexer, int i)
{
	while (lexer[i])
	{
		if (ft_strcmp(lexer[i], "<") == 0 || ft_strcmp(lexer[i], "<<") == 0)
			return (1);
		i++;
	}
	return (0);
}

int	is_redirection_output(char **lexer, int i)
{
	while (lexer[i])
	{
		if (ft_strcmp(lexer[i], ">") == 0 || ft_strcmp(lexer[i], ">>") == 0)
			return (1);
		i++;
	}
	return (0);
}
