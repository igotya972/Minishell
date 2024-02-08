/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afont <afont@student.42nice.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 11:00:54 by afont             #+#    #+#             */
/*   Updated: 2024/02/08 14:45:36 by afont            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_cd(t_data *data, char **inputs, int i)
{
	if (inputs[i + 1] && inputs[i + 2])
		printf("cd: too many arguments\n");
	else if (inputs[i + 1])
	{
		if (ft_strcmp(inputs[i + 1], "-") == 0)
		{
			if (data->oldpwd_status == 0)
				printf("cd: OLDPWD not set\n");
			else
			{
				ft_chdir(data, data->old_pwd);
				ft_pwd();
			}
		}
		else if (ft_strcmp(inputs[i + 1], "/") == 0)
			ft_chdir(data, "/");
		else if (ft_strcmp(inputs[i + 1], "~") == 0)
			ft_chdir(data, getenv("HOME"));
		else if (access(inputs[i + 1], F_OK) == -1)
			printf("cd: %s: No such file or directory\n", inputs[i + 1]);
		else
			ft_chdir(data, inputs[i + 1]);
	}
	else
		ft_chdir(data, getenv("HOME"));
}

void	ft_chdir(t_data *data, char *path)
{
	char	*tmp;

	tmp = getcwd(NULL, 0);
	chdir(path);
	if (data->old_pwd)
		free(data->old_pwd);
	data->old_pwd = tmp;
	data->oldpwd_status = 1;
	data->envp = envp_modifier(data);
	export_modifier(data);
}

void	export_modifier(t_data *data)
{
	char	**new_export;
	char	*tmp;

	new_export = malloc(sizeof(char *) * 2);
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
