/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afont <afont@student.42nice.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 16:39:43 by afont             #+#    #+#             */
/*   Updated: 2024/02/22 10:26:13 by afont            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

char	*envp_add2(t_data *data, char *key, char *value)
{
	char	*tmp;
	char	*tmp2;

	free(data->envp);
	tmp = ft_strjoin("", key);
	tmp2 = ft_strjoin(tmp, "=");
	free(tmp);
	tmp = ft_strjoin(tmp2, value);
	free(tmp2);
	return (tmp);
}

void	envp_add3(t_data *data, char **new_envp, char *tmp, int j)
{
	new_envp[j + 1] = tmp;
	new_envp[j + 2] = NULL;
	data->envp = new_envp;
}

void	ft_unset_env2(t_data *data, char **new_envp, int k)
{
	int	i;

	new_envp[k + 1] = NULL;
	i = -1;
	while (data->envp[++i])
		free(data->envp[i]);
	free(data->envp);
	data->envp = new_envp;
}
