/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afont <afont@student.42nice.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 11:01:13 by afont             #+#    #+#             */
/*   Updated: 2024/02/09 12:35:58 by afont            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_init_prompt(void)
{
	char	*prompt;
	char	*prompt2;
	char	*pwd;

	prompt = ft_strjoin("", "• \033[32mminishell\033[0;0m:\033[34m");
	pwd = getcwd(NULL, 0);
	prompt2 = ft_strjoin(prompt, pwd);
	free(prompt);
	free(pwd);
	prompt = ft_strjoin(prompt2, "\033[0;0m$ ");
	free(prompt2);
	return (prompt);
}

char	*ft_strjoin_carac(char const *s1, char const s2)
{
	size_t	i;
	char	*str;

	i = -1;
	if (!s1)
	{
		str = malloc(2);
		str[0] = s2;
		str[1] = '\0';
		return (str);
	}
	str = malloc(sizeof(char) * (ft_strlen(s1) + 2));
	if (!str)
		return (NULL);
	while (s1[++i])
		str[i] = s1[i];
	str[i] = s2;
	str[i + 1] = 0;
	return (str);
}