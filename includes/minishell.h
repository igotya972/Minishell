/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dferjul <dferjul@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 16:19:29 by dferjul           #+#    #+#             */
/*   Updated: 2024/01/12 16:19:29 by dferjul          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	char	**envp;
}				t_data;

typedef struct s_lexer
{
	//char	*input
}				t_lexer;



/*	minishell.c	*/
void	minishell_prompt(t_data *data);
void	exec_cmd(char *command);

/*	parser.c	*/
char	**lexer(t_data *input);

/*	ft_signal.c	*/
void	signal_manager(int signum);
void	set_signal_action(void);

/*	builtins.c	*/
int		ft_echo(t_data *data, char **inputs, int i);
void	launch_builtins(t_data *data, char **input);
void	ft_env(t_data *data);
void	ft_pwd(void);

/*	init_data.c	*/
void	init_data(t_data *data, char **envp);

#endif
