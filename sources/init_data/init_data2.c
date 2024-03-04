/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afont <afont@student.42nice.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 15:18:53 by afont             #+#    #+#             */
/*   Updated: 2024/02/22 10:26:59 by afont            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ft_export_str_init(char *key, char *value)
{
	char	*tmp_str;
	char	*tmp_str2;

	tmp_str = ft_strjoin("declare -x ", key);
	tmp_str2 = ft_strjoin(tmp_str, "=");
	free(tmp_str);
	if (value)
	{
		if (value[0] == '"' && value[ft_strlen(value) - 1] == '"')
		{
			tmp_str = ft_strjoin(tmp_str2, value);
			free(tmp_str2);
		}
		else
			tmp_str = ft_export_str_init2(tmp_str2, value);
	}
	else
	{
		tmp_str = ft_strjoin(tmp_str2, "\"\"");
		free(tmp_str2);
	}
	return (tmp_str);
}

char	*ft_export_str_init2(char *tmp_str2, char *value)
{
	char	*tmp_str;

	tmp_str = ft_strjoin(tmp_str2, "\"");
	free(tmp_str2);
	tmp_str2 = ft_strjoin(tmp_str, value);
	free(tmp_str);
	tmp_str = ft_strjoin(tmp_str2, "\"");
	free(tmp_str2);
	return (tmp_str);
}
