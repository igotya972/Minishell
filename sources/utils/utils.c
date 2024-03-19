/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afont <afont@student.42nice.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 11:01:13 by afont             #+#    #+#             */
/*   Updated: 2024/03/19 14:18:51 by afont            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

void	ft_protect_malloc(void *ptr)
{
	if (!ptr)
	{
		perror("Erreur d'allocation de mémoire");
		exit(EXIT_FAILURE);
	}
}

int	is_builtins(char *lexer_i)
{
	if (ft_strcmp(lexer_i, "echo") == 0)
		return (1);
	if (ft_strcmp(lexer_i, "cd") == 0)
		return (1);
	if (ft_strcmp(lexer_i, "pwd") == 0)
		return (1);
	if (ft_strcmp(lexer_i, "export") == 0)
		return (1);
	if (ft_strcmp(lexer_i, "unset") == 0)
		return (1);
	if (ft_strcmp(lexer_i, "env") == 0)
		return (1);
	if (ft_strcmp(lexer_i, "exit") == 0)
		return (1);
	return (0);
}

int	until_delimiteur(char **str, int i)
{
	while (str[i])
	{
		if (strcmp(str[i], "|") == 0)
			return (i);
		if (strcmp(str[i], ">") == 0)
			return (i);
		if (strcmp(str[i], "<") == 0)
			return (i);
		if (strcmp(str[i], ">>") == 0)
			return (i);
		if (strcmp(str[i], "<<") == 0)
			return (i);
		i++;
	}
	return (i - 1);
}

int	is_value_delimiteur(char c)
{
	char	delimiteur[8] = {'|', '>', '<', '"', ' ', '$', '\'', 17};
	int		i;
	i = -1;
	while (++i < 8)
		if (c == delimiteur[i])
			return (1);
	return (0);
}
