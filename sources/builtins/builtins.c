/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afont <afont@student.42nice.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 11:00:48 by afont             #+#    #+#             */
/*   Updated: 2024/03/19 14:20:34 by afont            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	launch_builtins(t_data *data, char **inputs, int i)
{
	char	*tmp;

	if (ft_strcmp(inputs[i], "exit") == 0)
		ft_exit(data, inputs, i);
	else if (ft_strcmp(inputs[i], "echo") == 0)
		i += ft_echo(inputs, i);
	else if (ft_strcmp(inputs[i], "pwd") == 0)
		ft_pwd(data);
	else if (ft_strcmp(inputs[i], "env") == 0)
		ft_env(data);
	else if (ft_strcmp(inputs[i], "cd") == 0)
	{
		tmp = ft_remove_control(inputs[i + 1]);
		ft_cd(data, inputs, i, tmp);
		free(tmp);
	}
	else
		launch_builtins2(data, inputs, i);
}

void	launch_builtins2(t_data *data, char **inputs, int i)
{
	if (ft_strcmp(inputs[i], "export") == 0)
	{
		if (!inputs[i + 1])
		{
			g_error = 0;
			ft_display_export(data);
		}
		else
			while (inputs[i + 1] && is_exec_delimiteur(inputs[i + 1]) != 1)
				ft_export(data, inputs, i++, 0);
	}
	else if (ft_strcmp(inputs[i], "unset") == 0)
	{
		g_error = 0;
		if (inputs[i + 1])
			while (inputs[i + 1] && is_exec_delimiteur(inputs[i + 1]) != 1)
				ft_unset(data, inputs, i++);
	}
}

int	ft_echo(char **inputs, int i)
{
	int	add;

	add = 0;
	if (inputs[i + 1])
	{
		if (ft_strcmp(inputs[i + 1], "-n") == 0)
			ft_echo2(inputs, &i, &add);
		else
		{
			while (inputs[++i] && is_exec_delimiteur(inputs[i]) != 1)
			{
				add++;
				printf("%s", inputs[i]);
				if (inputs[i + 1] && is_exec_delimiteur(inputs[i + 1]) != 1)
					printf(" ");
			}
			printf("\n");
		}
	}
	else
		printf("\n");
	g_error = 0;
	return (add);
}

void	ft_echo2(char **inputs, int *i, int *add)
{
	*add += 1;
	if (inputs[*i + 2])
	{
		while (inputs[++(*i) + 1] && is_exec_delimiteur(inputs[*i + 1]) != 1)
		{
			*add += 1;
			printf("%s", inputs[*i + 1]);
			if (inputs[*i + 2] && is_exec_delimiteur(inputs[*i + 2]) != 1)
				printf(" ");
		}
	}
	else
		return ;
}

void	ft_pwd(t_data *data)
{
	char	*tmp;

	tmp = getcwd(NULL, 0);
	if (!tmp)
		tmp = ft_strdup(data->recovery_pwd);
	printf("%s\n", tmp);
	free(tmp);
	g_error = 0;
}
