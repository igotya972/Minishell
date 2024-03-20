#include "../../includes/minishell.h"

void	delimiteur_modifier(char *tmp, char *input, int *i, int *j)
{
	if ((*i) != 0 && input[(*i) - 1] != ' ')
		tmp[++(*j)] = ' ';
	tmp[++(*j)] = input[(*i)];
	if (input[(*i) + 1] && input[(*i) + 1] == input[(*i)])
		tmp[++(*j)] = input[++(*i)];
	if (input[(*i) + 1] && input[(*i) + 1] != ' ')
		tmp[++(*j)] = ' ';
}

int	check_parse_error2(char **input, char **delimiteur, int i, int j)
{
	if (ft_strcmp(input[i], delimiteur[j]) == 0 && !input[i + 1])
	{
		printf("Minishell: parse error near `%s'\n", input[i]);
		g_error = 2;
		return (1);
	}
	if (ft_strcmp(input[i], delimiteur[j]) == 0 && input[i + 1] && ft_strcmp(input[i + 1], delimiteur[j]) == 0)
	{
		printf("Minishell: parse error near `%s'\n", input[i + 1]);
		g_error = 2;
		return (1);
	}
	return (0);
}

void	ft_add_history(char *input)
{
	static char	*old_input;

	if (!old_input)
	{
		old_input = ft_strdup(input);
		add_history(input);
	}
	else if (ft_strcmp(input, old_input) != 0)
		add_history(input);
	free(old_input);
	old_input = ft_strdup(input);
}