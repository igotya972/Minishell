/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afont <afont@student.42nice.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 14:11:22 by afont             #+#    #+#             */
/*   Updated: 2024/02/08 14:45:56 by afont            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_env(t_data *data)
{
	int	i;

	i = -1;
	while (data->envp[++i])
		printf("%s\n", data->envp[i]);
	if (data->oldpwd_status == 1)
		printf("OLDPWD=%s\n", data->old_pwd);
}

char	**envp_modifier(t_data *data)
{
	char	**new_envp;
	char	*tmp;
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
		{
			tmp = getcwd(NULL, 0);
			new_envp[i] = ft_strjoin("PWD=", tmp);
			free(tmp);
		}
		else
			new_envp[i] = ft_strdup(data->envp[i]);
	}
	new_envp[i] = NULL;
	i = -1;
	while (data->envp[++i])
		free(data->envp[i]);
	free(data->envp);
	return (new_envp);
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
	{
		if (!ft_strcmp(data->envp[i], key) == 0)
			new_envp[++j] = ft_strdup(data->envp[i]);
		free(data->envp[i]);
	}
	free(data->envp);
	tmp = ft_strjoin("", key);
	tmp2 = ft_strjoin(tmp, "=");
	free(tmp);
	tmp = ft_strjoin(tmp2, value);
	free(tmp2);
	new_envp[j] = tmp;
	new_envp[j + 1] = NULL;
	data->envp = new_envp;
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
		if (ft_strcmp(inputs[i + 1], data->envp[j]))
			new_envp[++k] = ft_strdup(data->envp[j]);
	new_envp[k + 1] = NULL;
	i = -1;
	while (data->envp[++i])
		free(data->envp[i]);
	free(data->envp);
	data->envp = new_envp;
}
