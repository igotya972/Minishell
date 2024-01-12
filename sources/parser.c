#include "../includes/minishell.h"

void	lexer(t_data *data)
{
	// ne pas split entre les guillemets ("salut                   s")
	data->lexer = ft_split(data->input, ' ');
}
