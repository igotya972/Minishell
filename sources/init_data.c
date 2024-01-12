#include 	"../includes/minishell.h"

void	init_data(t_data *data)
{
	data = malloc(sizeof(t_data));
	if (!data)
	{
		perror("Erreur d'allocation de mémoire");
		exit(EXIT_FAILURE);
	}
	data->env_path = getenv("PATH");
}