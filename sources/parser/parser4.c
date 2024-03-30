/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afont <afont@student.42nice.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 13:11:38 by afont             #+#    #+#             */
/*   Updated: 2024/03/19 17:05:22 by afont            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ft_delimiteur_to_control(char *s)
{
	int		j;
	char	*tmp;

	j = -1;
	tmp = NULL;
	while (s[++j])
	{
		if ((s[j] == '\"' || s[j] == '\'') && s[j + 1] && \
		is_parser_delimiteur(s[j + 1]) && s[j + 2] && \
		is_parser_delimiteur(s[j + 2]) && s[j + 3] && \
		(s[j + 3] == '\"' || s[j + 3] == '\''))
			s = add_control_preli(tmp, s, &j, 0);
		if ((s[j] == '\"' || s[j] == '\'') && s[j + 1] && \
		is_parser_delimiteur(s[j + 1]) && s[j + 2] && (s[j + 2] == \
		'\"' || s[j + 2] == '\''))
			s = add_control_preli(tmp, s, &j, 1);
	}
	tmp = ft_strdup(s);
	free(s);
	return (tmp);
}

char	*ft_addcontrol(char *str, int j, int flag)
{
	char	*tmp2;
	char	*tmp;

	tmp2 = malloc(sizeof(char) * (j + 4 - flag) + 1);
	ft_protect_malloc(tmp2);
	ft_strlcpy(tmp2, str, j + 4 - flag);
	tmp2[j + 3 - flag] = 18;
	tmp2[j + 4 - flag] = '\0';
	tmp = ft_strjoin(tmp2, str + j + 3 - flag);
	free(tmp2);
	return (tmp);
}

char	*add_control_preli(char *tmp, char *s, int *j, int flag)
{
	tmp = ft_addcontrol(s, *j, flag);
	free(s);
	*j = 0;
	return (tmp);
}
