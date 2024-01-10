# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <signal.h>
# include <string.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/libft.h"
# include <sys/wait.h>

#ifndef MINISHELL_H
# define MINISHELL_H

typedef struct  s_data
{
    char    *input;
    char    **lexer;
}               t_data;


/*	minishell.c	*/
void	minishell_prompt(void);
void    exec_cmd(char *command);

/*	parser.c	*/
char	**lexer(char *input);

/*  ft_signal.c */
void	signal_manager(int signum);
void	set_signal_action(void);

#endif
