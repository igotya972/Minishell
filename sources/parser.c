#include "../includes/minishell.h"

char	**lexer(char *input)
{
	//int	i = -1;
	char	**tab;
	tab = ft_split(input, ' ');
	//while (tab[++i])
	//	printf("%s\n", tab[i]);
	return (tab);
}
