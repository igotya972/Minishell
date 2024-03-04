/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afont <afont@student.42nice.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 08:53:18 by afont             #+#    #+#             */
/*   Updated: 2024/02/22 11:05:42 by afont            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	ft_export2(t_data *data, char **inputs, int i, int flag)
{
	int		j;
	char	*key;

	j = -1;
	while (inputs[i + 1][++j])
	{
		if (ft_isalnum(inputs[i + 1][j]) == 1 || \
		inputs[i + 1][j] == '_' || inputs[i + 1][j] == '=')
		{
			if (inputs[i + 1][j] == '=')
			{
				key = ft_keyinit(inputs[i + 1]);
				if (flag == 0)
					envp_add(data, key, inputs[i + 1] + j + 1);
				export_add(data, key, inputs[i + 1] + j + 1);
				return ;
			}
		}
		else
			return (ft_export3(inputs[i + 1]));
	}
	export_add(data, inputs[i + 1], NULL);
}

void	ft_export3(char *str)
{
	printf("export: not valid in this context: %s\n", str);
	return ;
}

void	ft_export_add4(t_data *data, int i)
{
	free(data->export[i].key);
	free(data->export[i].value);
}

t_export	*ft_export_add3(t_data *data)
{
	int			i;
	t_export	*tmp;

	i = 0;
	while (data->export[i].key)
		i++;
	tmp = malloc(sizeof(t_export) * (i + 2));
	ft_protect_malloc(tmp);
	return (tmp);
}

void	ft_export_add5(int *key_count, int *j, int *i)
{
	*key_count = 0;
	*j = -1;
	*i = -1;
}
