/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afont <afont@student.42nice.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 11:01:06 by afont             #+#    #+#             */
/*   Updated: 2024/02/08 11:01:07 by afont            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include 	"../includes/minishell.h"

void	init_data(t_data *data, char **envp)
{
	data->input = NULL;
	data->lexer = NULL;
	data->env_path = getenv("PATH");
	data->envp = init_envp(envp);
	data->old_pwd = NULL;
	data->oldpwd_status = 0;
	init_export(data);
}

char	**init_envp(char **envp)
{
	int		i;
	char	**tmp_envp;

	i = 0;
	while (envp[i])
		i++;
	tmp_envp = malloc(sizeof(char *) * (i + 1));
	i = -1;
	while (envp[++i])
		tmp_envp[i] = ft_strdup(envp[i]);
	tmp_envp[i] = NULL;
	return (tmp_envp);
}

void	init_export(t_data *data)
{
	int		i;

	i = 0;
	while (data->envp[i])
		i++;
	data->export = malloc(sizeof(t_export) * (i + 1));
	i = -1;
	while (data->envp[++i])
	{
		data->export[i].key = ft_keyinit(data->envp[i]);
		data->export[i].value = ft_valueinit(data->envp[i]);
		data->export[i].export_str = ft_export_str_init(data->export[i].key, data->export[i].value);
	}
	data->export[i].key = NULL;
	data->export[i].value = NULL;
	data->export[i].export_str = NULL;
}

char	*ft_export_str_init(char *key, char *value)
{
	char	*tmp_str;
	char 	*tmp_str2;

	tmp_str = ft_strjoin("declare -x ", key);
	tmp_str2 = ft_strjoin(tmp_str, "=");
	free(tmp_str);
	if (value)
	{
		if (value[0] == '"' && value[ft_strlen(value) - 1] == '"')
		{
			tmp_str = ft_strjoin(tmp_str2, value);
			free(tmp_str2);
		}
		else
		{
			tmp_str = ft_strjoin(tmp_str2, "\"");
			free(tmp_str2);
			tmp_str2 = ft_strjoin(tmp_str, value);
			free(tmp_str);
			tmp_str = ft_strjoin(tmp_str2, "\"");
			free(tmp_str2);
		}
	}
	else
	{
		tmp_str = ft_strjoin(tmp_str2, "\"\"");
		free(tmp_str2);
	}
	return (tmp_str);
}

char	*ft_keyinit(char *str)
{
	char	*tmp_key;
	int		i;
	int		j;

	j = 0;
	i = -1;
	while (str[++i] != '=')
		j++;
	tmp_key = malloc(sizeof(char) * (j + 1));
	i = -1;
	while (++i < j)
		tmp_key[i] = str[i];
	tmp_key[i] = '\0';
	return (tmp_key);
}

char	*ft_valueinit(char *str)
{
	char	*tmp_value;
	int		i;
	int		j;

	j = 0;
	i = -1;
	while (str[++i] != '=')
		j++;
	if (str[j + 1] == '\0')
		return (NULL);
	tmp_value = malloc(sizeof(char) * (ft_strlen(str) - j + 3));
	i = -1;
	tmp_value[++i] = '"';
	while (str[++j])
		tmp_value[++i] = str[j];
	tmp_value[++i] = '"';
	tmp_value[++i] = '\0';
	return (tmp_value);
}
