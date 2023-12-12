# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/libft.h"
# include <sys/wait.h>

#ifndef MINISHELL_H
# define MINISHELL_H

/*	minishell.c	*/
void	minishell_prompt(void);
void    exec_cmd(char *command);

/*	parser.c	*/
char	**lexer(char *input);

#endif
