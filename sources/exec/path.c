/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dferjul <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 01:25:44 by dferjul           #+#    #+#             */
/*   Updated: 2024/02/12 01:25:44 by dferjul          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**init_path(char **envp)
{
	int		i;
	char	**path;

	i = -1;
	while (envp[++i])
	{
		if (strncmp(envp[i], "PATH=", 5) == 0)
		{
			if (ft_strlen(envp[i]) < 6)
			{
				printf("Path is empty\n");
				return (NULL);
			}
			path = ft_split(&envp[i][5], ':');
			ft_protect_malloc(path);
			return (path);
		}
	}
	printf("Error get path\n");
	return (NULL);
}

static char	**add_slash(char **path)
{
	int		i;
	char	**path_slash;

	i = 0;
	if (!path)
		return (NULL);
	while (path[i])
		i++;
	path_slash = malloc(sizeof(char *) * (i + 1));
	ft_protect_malloc(path_slash);
	i = -1;
	while (path[++i])
		path_slash[i] = ft_strjoin(path[i], "/");
	path_slash[i] = NULL;
	return (path_slash);
}

char	*path_cmd(char **path, char *cmd)
{
	char	**path_slash;
	char	*cmd_path;
	int		i;

	i = -1;
	cmd_path = NULL;
	if (access(cmd, F_OK | X_OK) == 0)
		return (ft_strdup(cmd));
	path_slash = add_slash(path);
	while (path_slash[++i])
	{
		cmd_path = ft_strjoin(path_slash[i], cmd);
		if (access(cmd_path, F_OK | X_OK) == 0)
		{
			ft_free_tab(path_slash);
			return (cmd_path);
		}
		free(cmd_path);
	}
	ft_free_tab(path_slash);
	return (NULL);
}
