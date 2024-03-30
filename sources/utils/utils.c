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

#define D1 '|'
#define D2 '>'
#define D3 '<'
#define D4 '"'
#define D5 ' '
#define D6 '$'
#define D7 '\''
#define D8 17

char	*ft_init_prompt(t_data *data)
{
	char	*prompt;
	char	*prompt2;
	char	*pwd;

	prompt = ft_strjoin("", "• \033[32mminishell\033[0;0m:\033[34m");
	pwd = getcwd(NULL, 0);
	if (!pwd)
		pwd = ft_strdup(data->groot_pwd);
	else
	{
		free(data->groot_pwd);
		data->groot_pwd = ft_strdup(pwd);
		data->recovery_pwd = getcwd(NULL, 0); //leaks
	}
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
	char	delimiteur[8];
	int		i;

	delimiteur[0] = D1;
	delimiteur[1] = D2;
	delimiteur[2] = D3;
	delimiteur[3] = D4;
	delimiteur[4] = D5;
	delimiteur[5] = D6;
	delimiteur[6] = D7;
	delimiteur[7] = D8;
	i = -1;
	while (++i < 8)
		if (c == delimiteur[i])
			return (1);
	return (0);
}
