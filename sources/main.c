/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dferjul <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 19:38:04 by dferjul           #+#    #+#             */
/*   Updated: 2024/03/25 22:38:36 by dferjul          ###   ########.fr       */
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
	add_file_to_history();
	minishell_prompt(data);
	return (0);
}

// to do : qwe | asd (probleme)
// to do : exit 3 | exit (probleme code erreur) 
// to do : > qwe (probleme) + adqweasd > qwe (probleme)
// to do : t1 << t2 (probleme)
// to do : wc << t1 | cat << t2 (probleme)
// to do : wc << t1 | asd (probleme)
// to do : ./minishell |wc (probleme)
// to do : exit 3 | cd asd wqe | exit