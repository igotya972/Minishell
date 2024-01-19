#include "../includes/minishell.h"

void	ft_export(t_data *data, char **inputs, int i)
{
	int		j;
	char	*key;

	if (inputs[i + 1])
	{
		j = -1;
		while (inputs[i + 1][++j])
		{
			if (inputs[i + 1][j] == '=')
			{
				key = ft_keyinit(inputs[i + 1], j);
				data->envp = envp_add(data, key, inputs[i + 1] + j + 1);
				return ;
			}
		}
		printf("export: %s: not a valid identifier\n", inputs[i + 1]);
	}
	else
		ft_display_export(data);
}

char	*ft_keyinit(char *str, int j)
{
	char	*key;
	int		i;

	i = -1;
	key = malloc(sizeof(char) * (j + 1));
	while (++i < j)
		key[i] = str[i];
	key[i] = '\0';
	return (key);
}

char	**envp_add(t_data *data, char *key, char *value)
{
	char	**new_envp;
	int		i;
	char	*tmp;

	i = 0;
	while (data->envp[i])
		i++;
	new_envp = malloc(sizeof(char *) * (i + 1));
	i = -1;
	while (data->envp[++i])
		new_envp[i] = ft_strdup(data->envp[i]);
	tmp = ft_strjoin("", key);
	tmp = ft_strjoin(tmp, "=");
	tmp = ft_strjoin(tmp, value);
	new_envp[i] = tmp;
	new_envp[i + 1] = NULL;
	return (new_envp);
}

 void	ft_display_export(t_data *data)
{
 	int		i;
 	char	**tmp;
	int		envp_len;

 	envp_len = 0;
 	while (data->envp[envp_len])
 		envp_len++;
 	i = -1;
 	tmp = malloc(sizeof(char *) * (envp_len) + 1);
	while (++i < envp_len)
	{
		//tmp = ft_withquotation_marks(data->envp[i]);
		tmp[i] = ft_strdup(data->envp[i]);
		tmp[i] = ft_strjoin("declare -x ", tmp[i]);
	}
	tmp[i] = NULL;
	ft_sort_envp(tmp);
	i = -1;
	while (tmp[++i])
	{
		printf("%s\n", tmp[i]);
		free(tmp[i]);
	}
	free(tmp);
}

void	ft_sort_envp(char **envp)
{
	int		i;
	int		j;
	char	*tmp;

	i = -1;
	while (envp[++i])
	{
		j = i;
		while (envp[++j])
		{
			if (ft_strcmp(envp[i], envp[j]) > 0)
			{
				tmp = envp[i];
				envp[i] = envp[j];
				envp[j] = tmp;
			}
		}
	}
}

	
	
 	