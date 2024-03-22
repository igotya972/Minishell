/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dferjul <dferjul@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 19:38:04 by dferjul           #+#    #+#             */
/*   Updated: 2024/03/20 18:48:42 by dferjul          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	g_error;

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

// to do : arreter l'exec quand la commande echoue (code erreur?, cd asdjhfag > ls)
// to do : here doc
// to do : qwe | asd
// to do : exit 3 | exit
// to do : ls -la > qwe >> qwe (probleme)