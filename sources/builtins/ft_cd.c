/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afont <afont@student.42nice.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 11:00:54 by afont             #+#    #+#             */
/*   Updated: 2024/03/19 13:12:42 by afont            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_cd(t_data *data, char **inputs, int i, char *ctrl_rm)
{
	if (inputs[i + 1] && is_exec_delimiteur(inputs[i + 1]) \
	!= 1 && inputs[i + 2] && is_exec_delimiteur(inputs[i + 2]) != 1)
	{
		printf("cd: too many arguments\n");
		g_error = 1;
	}
	else if (inputs[i + 1] && is_exec_delimiteur(inputs[i + 1]) != 1)
	{
		if (ft_strcmp(inputs[i + 1], "-") == 0)
			ft_cd_minus(data);
		else if (ft_strcmp(inputs[i + 1], "/") == 0)
			g_error = ft_chdir(data, "/");
		else if (ft_strcmp(inputs[i + 1], "~") == 0)
			g_error = ft_chdir(data, getenv("HOME"));
		else if (access(ctrl_rm, F_OK) == -1)
		{
			printf("cd: %s: No such file or directory\n", inputs[i + 1]);
			g_error = 1;
		}
		else
			g_error = ft_chdir(data, ctrl_rm);
	}
	else
		g_error = ft_chdir(data, getenv("HOME"));
}

int	ft_chdir(t_data *data, char *path)
{
	char	*tmp;

	if (!path)
	{
		printf("minishell: cd: HOME not set\n");
		return (1);
	}
	tmp = getcwd(NULL, 0);
	chdir(path);
	if (data->old_pwd)
		free(data->old_pwd);
	data->old_pwd = tmp;
	data->oldpwd_status = 1;
	envp_add(data, "OLDPWD", data->old_pwd);
	data->envp = envp_modifier(data);
	export_modifier(data);
	return (0);
}

void	export_modifier(t_data *data)
{
	char	**new_export;
	char	*tmp;

	new_export = malloc(sizeof(char *) * 2);
	ft_protect_malloc(new_export);
	tmp = getcwd(NULL, 0);
	new_export[0] = ft_strdup("export");
	new_export[1] = ft_strjoin("PWD=", tmp);
	ft_export(data, new_export, 0, 1);
	free(tmp);
	free(new_export[0]);
	free(new_export[1]);
	new_export[0] = ft_strdup("export");
	new_export[1] = ft_strjoin("OLDPWD=", data->old_pwd);
	ft_export(data, new_export, 0, 1);
	free(new_export[0]);
	free(new_export[1]);
	free(new_export);
}

void	ft_cd_minus(t_data *data)
{
	if (data->oldpwd_status == 0)
	{
		printf("cd: OLDPWD not set\n");
		g_error = 1;
	}
	else
	{
		g_error = ft_chdir(data, data->old_pwd);
		ft_pwd();
	}
}
