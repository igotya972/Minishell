/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afont <afont@student.42nice.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 11:00:56 by afont             #+#    #+#             */
/*   Updated: 2024/02/22 11:07:54 by afont            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	ft_export(t_data *data, char **inputs, int i, int flag)
{
	if (ft_isalpha(inputs[i + 1][0]) != 0 || inputs[i + 1][0] == '_')
		ft_export2(data, inputs, i, flag);
	else
		printf("export: %s: not a valid identifier\n", inputs[i + 1]);
}

void	export_add(t_data *data, char *key, char *value)
{
	int			i;
	int			j;
	int			key_count;
	t_export	*tmp;

	tmp = ft_export_add3(data);
	ft_export_add5(&key_count, &j, &i);
	while (data->export[++i].key)
	{
		if (!ft_strcmp(data->export[i].key, key) \
		== 0 || (ft_strcmp(data->export[i].key, key) == 0 && !value))
		{
			tmp = ft_export_add7(data, tmp, &j, &i);
			if (ft_strcmp(data->export[i].key, key) == 0 && !value)
				key_count++;
		}
		else
			ft_export_add4(data, i);
	}
	if (!key_count || (key_count && value))
		tmp = ft_export_add6(tmp, value, key, &j);
	if (value)
		free(key);
	ft_export_add2(data, tmp, j);
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
