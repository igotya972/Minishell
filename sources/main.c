/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afont <afont@student.42nice.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 19:38:04 by dferjul           #+#    #+#             */
/*   Updated: 2024/02/09 11:17:53 by afont            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_data	*data;

	(void)argc;
	(void)argv;
	data = malloc(sizeof(t_data));
	if (!data)
	{
		perror("Erreur d'allocation de mémoire");
		exit(EXIT_FAILURE);
	}
	init_data(data, envp);
	minishell_prompt(data);
	return (0);
}

// to do : proteger les mallocs
// to do : leaks quand je fais export salut=salut
// to do : faire en sorte de remplacer vaar d'env ($COLORTERM par truecolor par exemple) dans le lexer
// to do : ne pas split entre les guillemets ("salut                   s") dans le lexer
// to do : prise en compte des pipes dans le lexer et ailleurs 

