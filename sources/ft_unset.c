#include 	"../includes/minishell.h"

void	ft_unset(t_data *data, char **inputs, int i)
{
	if (!inputs[i + 1])
		return ;
	if (ft_isalpha(inputs[i + 1][0]) != 0 || inputs[i + 1][0] == '_')
	{
		ft_unset_export(data, inputs, i);
		ft_unset_env(data, inputs, i);
	}
	else
		printf("export: %s: not a valid identifier\n", inputs[i + 1]);
}

void	ft_unset_export(t_data *data, char **inputs, int i)
{
	int			k;
	int			j;
	t_export	*tmp;

	k = 0;
	j = 0;
	while (data->export[k].key)
		k++;
	tmp = malloc(sizeof(t_export) * (k + 1));
	k = -1;
	while (data->export[++k].key)
	{
		if (ft_strncmp(inputs[i + 1], data->export[k].key, ft_strlen(data->export[k].key)))
		{
			// printf("%s, ", data->export[k].key);
			// printf("%s                                                                                                                                                                                     ", data->export[k].value);
			//printf("%s                                                                                                         ", data->export[k].export_str);
			tmp[j].key = ft_strdup(data->export[k].key);
			if (data->export[k].value)
				tmp[j].value = ft_strdup(data->export[k].value);
			else
				tmp[j].value = NULL;
			tmp[j].export_str = ft_strdup(data->export[k].export_str);
			j++;
		}
	}
	tmp[j + 1].key = NULL;
	tmp[j + 1].value = NULL;
	tmp[j + 1].export_str = NULL;
	//free(data->export);
	data->export = tmp;
}

void	ft_unset_env(t_data *data, char **inputs, int i)
{
	int		j;
	int		k;
	char	**new_envp;

	j = 0;
	while (data->envp[j])
		j++;
	new_envp = malloc(sizeof(char *) * (j + 1));
	j = -1;
	k = -1;
	while (data->envp[++j])
		if (ft_strncmp(inputs[i + 1], data->envp[j], ft_strlen(inputs[i + 1])))
			new_envp[++k] = ft_strdup(data->envp[j]);
	new_envp[k + 1] = NULL;
	//free(data->envp);
	data->envp = new_envp;
}
