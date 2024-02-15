/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afont <afont@student.42nice.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 11:01:13 by afont             #+#    #+#             */
/*   Updated: 2024/02/15 10:34:07 by afont            ###   ########.fr       */
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
