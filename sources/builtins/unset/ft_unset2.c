/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afont <afont@student.42nice.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 15:14:59 by afont             #+#    #+#             */
/*   Updated: 2024/02/22 10:26:43 by afont            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	ft_unset2(t_data *data, t_export *tmp, int j)
{
	int	k;

	tmp[j + 1].key = NULL;
	tmp[j + 1].value = NULL;
	tmp[j + 1].export_str = NULL;
	k = -1;
	while (data->export[++k].key)
	{
		free(data->export[k].key);
		free(data->export[k].value);
		free(data->export[k].export_str);
	}
	free(data->export);
	data->export = tmp;
}

t_export	*ft_unset3(t_data *data)
{
	int			i;
	t_export	*tmp;

	i = 0;
	while (data->export[i].key)
		i++;
	tmp = malloc(sizeof(t_export) * (i + 1));
	ft_protect_malloc(tmp);
	return (tmp);
}
