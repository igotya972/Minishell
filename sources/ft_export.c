/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afont <afont@student.42nice.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 11:00:56 by afont             #+#    #+#             */
/*   Updated: 2024/02/19 13:40:30 by afont            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_export(t_data *data, char **inputs, int i, int flag)
{
	int		j;
	char	*key;

	j = -1;
	if (ft_isalpha(inputs[i + 1][0]) != 0 || inputs[i + 1][0] == '_')
	{
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
			{
				printf("export: not valid in this context: %s\n", \
				inputs[i + 1]);
				return ;
			}
		}
		export_add(data, inputs[i + 1], NULL);
	}
	else
		printf("export: %s: not a valid identifier\n", inputs[i + 1]);
}

void	export_add(t_data *data, char *key, char *value)
{
	int			i;
	int			j;
	int			key_count;
	t_export	*tmp;

	i = 0;
	j = -1;
	key_count = 0;
	while (data->export[i].key)
		i++;
	tmp = malloc(sizeof(t_export) * (i + 2));
	ft_protect_malloc(tmp);
	i = -1;
	while (data->export[++i].key)
	{
		if (!ft_strcmp(data->export[i].key, key) \
		== 0 || (ft_strcmp(data->export[i].key, key) == 0 && !value))
		{
			tmp[++j].key = data->export[i].key;
			tmp[j].value = data->export[i].value;
			tmp[j].export_str = \
			ft_export_str_init(data->export[i].key, data->export[i].value);
			if (ft_strcmp(data->export[i].key, key) == 0 && !value)
				key_count++;
		}
		else
		{
			free(data->export[i].key);
			free(data->export[i].value);
		}
	}
	if (!key_count || (key_count && value))
	{
		tmp[++j].key = ft_strdup(key);
		tmp[j].value = ft_value_with_quotation_mark(value);
		tmp[j].export_str = ft_export_str_init(key, value);
	}
	if (value)
		free(key);
	tmp[j + 1].key = NULL;
	tmp[j + 1].value = NULL;
	tmp[j + 1].export_str = NULL;
	i = -1;
	while (data->export[++i].export_str)
		free(data->export[i].export_str);
	free(data->export);
	data->export = tmp;
}

char	*ft_value_with_quotation_mark(char *value)
{
	char	*tmp;
	char	*tmp2;

	tmp = ft_strjoin("\"", value);
	tmp2 = ft_strjoin(tmp, "\"");
	free(tmp);
	return (tmp2);
}

void	ft_display_export(t_data *data)
{
	int	i;

	ft_sort_export(data->export);
	i = -1;
	while (data->export[++i].key)
		printf("%s\n", data->export[i].export_str);
}

void	ft_sort_export(t_export *export)
{
	int			i;
	int			j;
	t_export	tmp;

	i = -1;
	while (export[++i].key)
	{
		j = i;
		while (export[++j].key)
		{
			if (ft_strcmp(export[i].key, export[j].key) > 0)
			{
				tmp = export[i];
				export[i] = export[j];
				export[j] = tmp;
			}
		}
	}
}
