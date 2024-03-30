/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afont <afont@student.42nice.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 17:43:27 by afont             #+#    #+#             */
/*   Updated: 2024/03/30 17:46:09 by afont            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_strlen_gnl(char *str)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*after_newline(char *buff)
{
	int		i;
	int		j;
	char	*new_buff;

	if (!is_newline(buff))
	{
		free(buff);
		return (NULL);
	}
	i = 0;
	j = 0;
	new_buff = malloc(ft_strlen_gnl(buff));
	while (buff[i] != '\n')
		i++;
	i++;
	while (buff[i])
		new_buff[j++] = buff[i++];
	new_buff[j] = 0;
	free(buff);
	return (new_buff);
}

int	is_newline(char *buff)
{
	int	i;

	i = -1;
	while (buff && buff[++i])
		if (buff[i] == '\n')
			return (1);
	return (0);
}

char	*del_newline(char *buff)
{
	int		i;
	int		buff_len;
	char	*new_buff;

	if (!buff)
		return (NULL);
	i = 0;
	buff_len = ft_strlen_gnl(buff);
	new_buff = malloc(buff_len + 1);
	while (buff[i] != '\n' && buff[i])
	{
		new_buff[i] = buff[i];
		i++;
	}
	if (buff[i] && buff[i] == '\n')
	{
		new_buff[i] = '\n';
		new_buff[++i] = 0;
	}
	else
		new_buff[i] = 0;
	return (new_buff);
}

char	*ft_strjoin_gnl(char *s1, char *s2)
{
	char	*t;
	int		i;

	i = 0;
	t = malloc(ft_strlen_gnl((char *)s1) + ft_strlen_gnl((char *)s2) + 1);
	if (!t)
		return (NULL);
	while (s1 && *s1)
		t[i++] = *s1++;
	while (s2 && *s2)
		t[i++] = *s2++;
	if (i == 0)
	{
		free(t);
		return (NULL);
	}
	t[i] = 0;
	return (t);
}
