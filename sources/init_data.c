#include 	"../includes/minishell.h"

void	init_data(t_data *data, char **envp)
{
	data->input = NULL;
	data->lexer = NULL;
	data->env_path = getenv("PATH");
	data->envp = envp;
}