#include "../includes/minishell.h"

char	**lexer(char *input)
{
	char	**tab;

	tab = ft_split(input, ' ');
	return (tab);
}
