/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afont <afont@student.42nice.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 11:00:48 by afont             #+#    #+#             */
/*   Updated: 2024/02/29 13:53:40 by afont            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	launch_builtins(t_data *data, char **inputs, int i)
{
	char	*tmp;

	if (ft_strcmp(inputs[i], "exit") == 0)
		ft_free(data);
	else if (ft_strcmp(inputs[i], "echo") == 0)
		i += ft_echo(data, inputs, i);
	else if (ft_strcmp(inputs[i], "pwd") == 0)
		ft_pwd();
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
			ft_display_export(data);
		else
			while (inputs[i + 1] && is_exec_delimiteur(inputs[i + 1]) != 1)
				ft_export(data, inputs, i++, 0);
	}
	else if (ft_strcmp(inputs[i], "unset") == 0)
	{
		if (inputs[i + 1])
			while (inputs[i + 1] && is_exec_delimiteur(inputs[i + 1]) != 1)
				ft_unset(data, inputs, i++);
	}
}

int	ft_echo(t_data *data, char **inputs, int i)
{
	int	add;

	add = 0;
	if (inputs[i + 1])
	{
		if (ft_strcmp(inputs[i + 1], "-n") == 0)
			ft_echo2(data, inputs, &i, &add);
		else
		{
			while (inputs[++i] && is_exec_delimiteur(inputs[i]) != 1)
			{
				add++;
				printf("%s ", inputs[i]);
			}
			printf("\n");
		}
	}
	else
		printf("\n");
	return (add);
}

void	ft_echo2(t_data *data, char **inputs, int *i, int *add)
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
		minishell_prompt(data);
}

void	ft_pwd(void)
{
	char	*tmp;

	tmp = getcwd(NULL, 0);
	printf("%s\n", tmp);
	free(tmp);
}
