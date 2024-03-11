/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afont <afont@student.42nice.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 03:03:07 by dferjul           #+#    #+#             */
/*   Updated: 2024/03/01 11:01:38 by afont            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_free(t_data *data)
{
	int	i;

	i = -1;
	if (data->export[0].key)
	{
		while (data->export[++i].key)
		{
			free(data->export[i].key);
			free(data->export[i].value);
			free(data->export[i].export_str);
		}
		free(data->export);
	}
	if (data->input)
		free(data->input);
	ft_free2(data);
}

void	ft_free2(t_data *data)
{
	int	i;

	if (data->envp[0])
	{
		i = -1;
		while (data->envp[++i])
			free(data->envp[i]);
		free(data->envp);
	}
	if (data->old_pwd)
		free(data->old_pwd);
	if (data->path)
	{
		i = -1;
		while (data->path[++i])
			free(data->path[i]);
		free(data->path);
	}
	free(data);
	exit(EXIT_SUCCESS);
}


void	ft_free_tab(char **tab)
{
	int	i;

	i = -1;
	while (tab[++i])
		free(tab[i]);
	free(tab);
}
