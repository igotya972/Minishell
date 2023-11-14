#include "../includes/minishell.h"

		// Affiche le prompt
void	minishell_prompt(void)
{
    char	*input;
	
	while (1) 
	{
		input = readline("minishell>");
		add_history(input);
		//printf("Vous avez entré : %s\n", input);
		if (strcmp(input, "exit") == 0)
			return ;
	}
}

int main()
{
	minishell_prompt();
	return 0;
}