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
				data->export_str = export_add(data, key, inputs[i + 1] + j + 1);
				return ;
			}
		}
		//data->export_str = envp_add(data, inputs[i + 1], "");
		data->export_str = export_add(data, inputs[i + 1], NULL);
		//printf("export: %s: not a valid identifier\n", inputs[i + 1]);
	}
	else
		ft_display_export(data);
}

char 	**export_add(t_data *data, char *key, char *value)
{
	char	**new_export;
	int		i;
	char	*tmp;

	i = 0;
	while (data->export_str[i])
		i++;
	new_export = malloc(sizeof(char *) * (i + 1));
	i = -1;
	while (data->export_str[++i])
		new_export[i] = ft_strdup(data->export_str[i]);
	tmp = ft_strjoin("", key);
	if (value)
	{
		tmp = ft_strjoin(tmp, "=");
		tmp = ft_strjoin(tmp, value);
	}
	new_export[i] = tmp;
	new_export[i + 1] = NULL;
	return (new_export);
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
	int		export_len;

 	export_len = 0;
 	while (data->export_str[export_len])
 		export_len++;
 	i = -1;
 	tmp = malloc(sizeof(char *) * (export_len) + 1);
	while (++i < export_len)
	{
		tmp[i] = ft_with_quotation_marks(data->export_str[i]);
		tmp[i] = ft_strjoin("declare -x ", tmp[i]);
	}
	tmp[i] = NULL;
	ft_sort_export(tmp);
	i = -1;
	while (tmp[++i])
		printf("%s\n", tmp[i]);
}

void	ft_sort_export(char **export)
{
	int		i;
	int		j;
	char	*tmp;

	i = -1;
	while (export[++i])
	{
		j = i;
		while (export[++j])
		{
			if (ft_strcmp(export[i], export[j]) > 0)
			{
				tmp = export[i];
				export[i] = export[j];
				export[j] = tmp;
			}
		}
	}
}

char	*ft_with_quotation_marks(char *str)
{
	int		i;
	int		j;
	char	*tmp;

	tmp = ft_calloc(sizeof(char *), (ft_strlen(str) + 3));	
	i = -1;
	j = -1;
	while (str[++i])
	{
		tmp[++j] = str[i];
		if (str[i] == '=')
			break;
	}
	if (str[i] != '=')
		return (tmp);
	tmp[++j] = '"';
	while (str[++i])
	{
		if (str[i] == '\n')
			break;
		tmp[++j] = str[i];
	}
	tmp[j + 1] = '"';
	tmp[j + 2] = '\0';
	return (tmp);
}
			