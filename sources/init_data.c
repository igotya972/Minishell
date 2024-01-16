#include 	"../includes/minishell.h"

void	init_data(t_data *data, char **envp)
{
	data->input = NULL;
	data->lexer = NULL;
	data->env_path = getenv("PATH");
	data->envp = envp;
}

char	**envp_without_oldpwd(char **envp)
{
	int		i;
	char	**new_envp;

	i = 0;
	while (envp[i])
		i++;
	new_envp = malloc(sizeof(char *) * (i + 1));
	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "OLDPWD=", 7) == 0)
			i++;
		else
		{
			new_envp[i] = ft_strdup(envp[i]);
			i++;
		}
	}
	new_envp[i] = NULL;
	return (new_envp);
}