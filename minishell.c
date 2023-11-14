/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dferjul <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 10:44:03 by dferjul           #+#    #+#             */
/*   Updated: 2023/11/14 10:44:03 by dferjul          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

		// Affiche le prompt
void	minishell_prompt(void)
{
	char	*input;

	input = NULL;
	while (1) {
		printf("minishell> ");

		if (fgets(input, MAX_INPUT_SIZE, stdin) == NULL)
		{
			fprintf(stderr, "Erreur lors de la lecture de l'entrée.\n");
			exit(EXIT_FAILURE);
		}

		// Supprime le saut de ligne à la fin de l'entrée
		size_t	input_len;
		input_len = strlen(input);
		if (input_len > 0 && input[input_len - 1] == '\n')
		{
			input[input_len - 1] = '\0';
		}

		printf("Vous avez entré : %s\n", input);
		if (strcmp(input, "exit") == 0)
		{
			printf("Au revoir!\n");
			break;
		}
	}
}

int main()
{
	minishell_prompt();
	return 0;
}
