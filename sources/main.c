/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afont <afont@student.42nice.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 19:38:04 by dferjul           #+#    #+#             */
/*   Updated: 2024/02/19 11:42:50 by afont            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_data	*data;

	(void)argc;
	(void)argv;
	data = malloc(sizeof(t_data));
	ft_protect_malloc(data);
	init_data(data, envp);
	minishell_prompt(data);
	return (0);
}

// to do : proteger les mallocs
// to do : leaks quand je fais export salut=salut
// to do : prise en compte des pipes dans le lexer et ailleurs 
// to do : prise en compte des simple quotes dans le lexer
// to do : affiche double prompt quand tu fait wc -l