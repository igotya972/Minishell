/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afont <afont@student.42nice.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 19:38:04 by dferjul           #+#    #+#             */
/*   Updated: 2024/02/29 13:52:32 by afont            ###   ########.fr       */
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

// to do : prise en compte des pipes dans le lexer et ailleurs 
// to do : affiche double prompt quand tu fait wc -l
// to do : gerer leaks dans l'exec
// to do : utiliser le lexer dans l'exec
// to do : faire en sorte que toutes les fonctions s'arettent quand on croise un delimiteur (echo asd> asd)
// to do : salut ca va > > asd (parse error near `>')
