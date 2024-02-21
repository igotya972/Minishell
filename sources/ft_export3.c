/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afont <afont@student.42nice.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 11:11:56 by afont             #+#    #+#             */
/*   Updated: 2024/02/21 14:59:23 by afont            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_export_add2(t_data *data, t_export *tmp, int j)
{
	int	i;

	tmp[j + 1].key = NULL;
	tmp[j + 1].value = NULL;
	tmp[j + 1].export_str = NULL;
	i = -1;
	while (data->export[++i].export_str)
		free(data->export[i].export_str);
	free(data->export);
	data->export = tmp;
}

t_export	*ft_export_add6(t_export *tmp, char *value, char *key, int *j)
{
	tmp[*(++j)].key = ft_strdup(key);
	tmp[*j].value = ft_value_with_quotation_mark(value);
	tmp[*j].export_str = ft_export_str_init(key, value);
	return (tmp);
}

t_export	*ft_export_add7(t_data *data, t_export *tmp, int *j, int *i)
{
	tmp[++(*j)].key = data->export[*i].key;
	tmp[*j].value = data->export[*i].value;
	tmp[*j].export_str = \
	ft_export_str_init(data->export[*i].key, data->export[*i].value);
	return (tmp);
}
