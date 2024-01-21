#include 	"../includes/minishell.h"

void	init_data(t_data *data, char **envp)
{
	data->input = NULL;
	data->lexer = NULL;
	data->env_path = getenv("PATH");
	data->envp = envp;
	data->old_pwd = NULL;
	data->oldpwd_status = 0;
	data->export_str = init_export(envp);
}


char	**init_export(char **envp)
{
	char	**export_str;
	int		i;

	i = 0;
	while (envp[i])
		i++;
	export_str = malloc(sizeof(char *) * (i + 1));
	i = -1;
	while (envp[++i - 1])
		export_str[i] = ft_strdup(envp[i]);
	export_str[i + 1] = NULL;
	return (export_str);
}