#include "../includes/minishell.h"
void	ft_export(t_data *data, char **inputs, int i, int flag)
{
	int		j;
	char	*key;

	j = -1;
	if (ft_isalpha(inputs[i + 1][0]) != 0 || inputs[i + 1][0] == '_')
	{
		while (inputs[i + 1][++j])
		{
			if (inputs[i + 1][j] == '=')
			{
				key = ft_keyinit(inputs[i + 1]);
				if (flag == 0)
					envp_add(data, key, inputs[i + 1] + j + 1);
				export_add(data, key, inputs[i + 1] + j + 1);
				return ;
			}
		}
		export_add(data, inputs[i + 1], NULL);
	}
	else
		printf("export: %s: not a valid identifier\n", inputs[i + 1]);
}

void	export_add(t_data *data, char *key, char *value)
{
	int			i;
	int			j;
	int			key_count;
	int			old_export_len;
	t_export	*tmp;

	i = 0;
	j = -1;
	key_count = 0;
	old_export_len = data->export_len;
	while (data->export[i].key)
		i++;
	tmp = malloc(sizeof(t_export) * (i + 2));
	i = -1;
	data->export_len = 0;
	while (data->export[++i].key)
	{
		if (!ft_strcmp(data->export[i].key, key) == 0 || (ft_strcmp(data->export[i].key, key) == 0 && !value))
		{
			tmp[++j].key = data->export[i].key;
			tmp[j].value = data->export[i].value;
			tmp[j].export_str = ft_export_str_init(data->export[i].key, data->export[i].value);
			data->export_len += 1;
			if (ft_strcmp(data->export[i].key, key) == 0 && !value)
				key_count++;
		}
		else
		{
			free(data->export[i].key);
			free(data->export[i].value);
		}
	}
	if (!key_count || (key_count && value))
	{
		tmp[++j].key = ft_strdup(key);
		tmp[j].value = ft_value_with_quotation_mark(value);
		tmp[j].export_str = ft_export_str_init(key, value);
		data->export_len += 1;
	}
	else
		free(key);
	tmp[j + 1].key = NULL;
	tmp[j + 1].value = NULL;
	tmp[j + 1].export_str = NULL;
	i = -1;
	while (++i < old_export_len)
		free(data->export[i].export_str);
	free(data->export);
	data->export = tmp;
}

char	*ft_value_with_quotation_mark(char *value)
{
	char	*tmp;
	char	*tmp2;

	tmp = ft_strjoin("\"", value);
	tmp2 = ft_strjoin(tmp, "\"");
	free(tmp);
	return (tmp2);
}

void	envp_add(t_data *data, char *key, char *value)
{
	char	**new_envp;
	int		i;
	int		j;
	char	*tmp;
	char	*tmp2;

	i = 0;
	while (data->envp[i])
		i++;
	new_envp = malloc(sizeof(char *) * (i + 1));
	i = -1;
	j = -1;
	while (data->envp[++i])
		if (!ft_strncmp(data->envp[i], key, ft_strlen(key)) == 0)
			new_envp[++j] = ft_strdup(data->envp[i]);
	tmp = ft_strjoin("", key);
	tmp2 = ft_strjoin(tmp, "=");
	free(tmp);
	tmp = ft_strjoin(tmp2, value);
	free(tmp2);
	new_envp[j] = tmp;
	new_envp[j + 1] = NULL;
	i = -1;
	while (data->envp[++i])
		free(data->envp[i]);
	free(data->envp);
	data->envp = new_envp;
}

void	ft_display_export(t_data *data)
{
 	int	i;

	ft_sort_export(data->export);
	i = -1;
	while (data->export[++i].key)
		printf("%s\n", data->export[i].export_str);
}

void	ft_sort_export(t_export *export)
{
	int		i;
	int		j;
	t_export	tmp;

	i = -1;
	while (export[++i].key)
	{
		j = i;
		while (export[++j].key)
		{
			if (ft_strcmp(export[i].key, export[j].key) > 0)
			{
				tmp = export[i];
				export[i] = export[j];
				export[j] = tmp;
			}
		}
	}
}