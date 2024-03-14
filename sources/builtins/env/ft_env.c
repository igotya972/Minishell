/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afont <afont@student.42nice.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 14:11:22 by afont             #+#    #+#             */
/*   Updated: 2024/02/22 10:26:05 by afont            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	ft_env(t_data *data)
{
	int	i;

	i = -1;
	while (data->envp[++i])
		printf("%s\n", data->envp[i]);
	g_error = 0;
}

char	**envp_modifier(t_data *data)
{
	char	**new_envp;
	int		i;

	data->env_path = getenv("PATH");
	i = 0;
	while (data->envp[i])
		i++;
	new_envp = envp_modifier2(data, i);
	i = -1;
	while (data->envp[++i])
		free(data->envp[i]);
	free(data->envp);
	return (new_envp);
}

char	**envp_modifier2(t_data *data, int i)
{
	char	*tmp;
	char	**new_envp;

	new_envp = malloc(sizeof(char *) * (i + 1));
	ft_protect_malloc(new_envp);
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
	return (new_envp);
}

void	envp_add(t_data *data, char *key, char *value)
{
	char	**new_envp;
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	while (data->envp[i])
		i++;
	new_envp = malloc(sizeof(char *) * (i + 2));
	ft_protect_malloc(new_envp);
	i = -1;
	j = -1;
	while (data->envp[++i])
	{
		tmp = ft_keyinit(data->envp[i]);
		if (!ft_strcmp(tmp, key) == 0)
			new_envp[++j] = ft_strdup(data->envp[i]);
		free(data->envp[i]);
		free(tmp);
	}
	tmp = envp_add2(data, key, value);
	envp_add3(data, new_envp, tmp, j);
}

void	ft_unset_env(t_data *data, char **inputs, int i)
{
	int		j;
	int		k;
	char	**new_envp;
	char	*tmp;

	j = 0;
	while (data->envp[j])
		j++;
	new_envp = malloc(sizeof(char *) * (j + 1));
	ft_protect_malloc(new_envp);
	j = -1;
	k = -1;
	while (data->envp[++j])
	{
		tmp = ft_keyinit(data->envp[j]);
		if (ft_strncmp(inputs[i + 1], "OLDPWD", 6) == 0)
			data->oldpwd_status = 0;
		if (ft_strcmp(inputs[i + 1], tmp))
			new_envp[++k] = ft_strdup(data->envp[j]);
		free(tmp);
	}
	ft_unset_env2(data, new_envp, k);
}
