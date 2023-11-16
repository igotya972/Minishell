# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/libft.h"

#ifndef MINISHELL_H
# define MINISHELL_H

/*	minishell.c	*/
void	minishell_prompt(void);

/*	parser.c	*/
char	**lexer(char *input);

#endif