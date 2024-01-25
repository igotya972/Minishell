#include "../includes/minishell.h"

void	ft_cd(t_data *data, char **inputs, int i)
{
	(void)data;
	if (inputs[i + 1] && inputs[i + 2])
		printf("cd: too many arguments\n");
	else if (inputs[i + 1])
	{
		if (access(inputs[i + 1], F_OK) == -1)
			printf("cd: %s: No such file or directory\n", inputs[i + 1]);
		else
		{
			data->old_pwd = getcwd(NULL, 0);
			chdir(inputs[i + 1]);
			data->oldpwd_status = 1;
			data->envp = envp_modifier(data);
			export_modifier(data);
		}
	}
	else
	{
		data->old_pwd = getcwd(NULL, 0);
		chdir(getenv("HOME"));
		data->oldpwd_status = 1;
		data->envp = envp_modifier(data);
		export_modifier(data);
	}

}

void	export_modifier(t_data *data)
{
	char	**new_export;

	new_export = malloc(sizeof(char *) * 2);
	new_export[0] = ft_strdup("export");
	new_export[1] = ft_strjoin("PWD=", getcwd(NULL, 0));
	ft_export(data, new_export, 0, 1);
	new_export[0] = ft_strdup("export");
	new_export[1] = ft_strjoin("OLDPWD=", data->old_pwd);
	ft_export(data, new_export, 0, 1);
	free(new_export[0]);
	free(new_export[1]);
	free(new_export);
}

char	**envp_modifier(t_data *data)
{
	char	**new_envp;
	int		i;

	data->env_path = getenv("PATH");
	i = 0;
	while (data->envp[i])
		i++;
	new_envp = malloc(sizeof(char *) * (i + 1));
	i = -1;
	while (data->envp[++i])
	{
		if (ft_strncmp(data->envp[i], "OLDPWD=", 7) == 0)
			new_envp[i] = ft_strjoin("OLDPWD=", data->old_pwd);
		else if (ft_strncmp(data->envp[i], "PWD=", 4) == 0)
			new_envp[i] = ft_strjoin("PWD=", getcwd(NULL, 0));
		else
			new_envp[i] = ft_strdup(data->envp[i]);
	}
	new_envp[i] = NULL;
	return (new_envp);
}