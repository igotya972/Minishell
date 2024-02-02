#include "../includes/minishell.h"

char	*ft_init_prompt(void)
{
	char	*prompt;
	char	*prompt2;
	char	*pwd;

	//  ft_strjoin("\033[32mminishell\033[0;0m:\033[34m ", getcwd(NULL, 0))
	//  ft_strjoin(truc au dessus, "\033[0;0m$ ")
	// ft_strjoin(ft_strjoin("• \033[32mminishell\033[0;0m:\033[34m", getcwd(NULL, 0)), "\033[0;0m$ ")
	prompt = ft_strjoin("", "• \033[32mminishell\033[0;0m:\033[34m");
	pwd = getcwd(NULL, 0);
	prompt2 = ft_strjoin(prompt, pwd);
	free(prompt);
	free(pwd);
	prompt = ft_strjoin(prompt2, "\033[0;0m$ ");
	free(prompt2);
	return (prompt);
}
