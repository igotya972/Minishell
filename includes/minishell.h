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

typedef struct	s_data
{
	char	*input;
	char	**lexer;
}				t_data;


/*	minishell.c	*/
void	minishell_prompt(void);
void	exec_cmd(char *command);

/*	parser.c	*/
void	lexer(t_data *data);

/*	ft_signal.c	*/
void	signal_manager(int signum);
void	set_signal_action(void);

/*	builtins.c	*/
void	ft_echo(char **inputs, int i);
void	launch_builtins(char **input);

#endif
