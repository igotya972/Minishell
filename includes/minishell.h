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
	char	*env_path;
}				t_data;


/*	minishell.c	*/
void	minishell_prompt(t_data *data);
void	exec_cmd(char *command);

/*	parser.c	*/
void	lexer(t_data *data);

/*	ft_signal.c	*/
void	signal_manager(int signum, t_data *data);
void	set_signal_action(void);

/*	builtins.c	*/
int		ft_echo(t_data *data, char **inputs, int i);
void	launch_builtins(t_data *data, char **input);
void	ft_pwd(void);

/*	init_data.c	*/
void	init_data(t_data *data);

#endif
