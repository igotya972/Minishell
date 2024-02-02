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

typedef struct s_data	t_data;
typedef struct s_export	t_export;

struct	s_export
{
	char	*key;
	char	*value;
	char	*export_str;
};

struct	s_data
{
	char		*input;
	char		**lexer;
	char		*env_path;
	char		**envp;
	char		*old_pwd;
	int			oldpwd_status;
	t_export	*export;
};

typedef struct s_lexer
{
	//char	*input
}				t_lexer;


/*	ft_signal.c	*/
void	signal_manager(int signum);
void	handle_ctrld(t_data *data);

/*	minishell.c	*/
void	minishell_prompt(t_data *data);

/*	exec_cmd.c	*/
void	execute_ls(void);
void	exec_cmd(char *command);

/*	parser.c	*/
void	lexer_temporaire(t_data *data);
int		count_tokens(t_data *data);
char	*append_char_to_token(char **token, char c);
char	**lexer(t_data *data);

/*	builtins.c	*/
int		ft_echo(t_data *data, char **inputs, int i);
void	launch_builtins(t_data *data, char **input);
void	ft_env(t_data *data);
void	ft_pwd(void);

/*	ft_cd.c		*/
void	ft_cd(t_data *data, char **inputs, int i);
char	**envp_modifier(t_data *data);
void	export_modifier(t_data *data);
void	ft_chdir(t_data *data, char *path);

/*	init_data.c	*/
void	init_data(t_data *data, char **envp);
void	init_export(t_data *data);
char	*ft_keyinit(char *str);
char	*ft_valueinit(char *str);
char	*ft_export_str_init(char *key, char *value);
char * NewFunction(char * tmp_str);
char **init_envp(char **envp);

/*	free.c		*/
void free_arguments(char **args);
void	ft_free(t_data *data);

/*	ft_export.c	*/
void	ft_export(t_data *data, char **inputs, int i, int flag);
char	**envp_add(t_data *data, char *key, char *value);
void	ft_display_export(t_data *data);
void	export_add(t_data *data, char *key, char *value);
void	ft_sort_export(t_export *export);
char	*ft_value_with_quotation_mark(char *value);

/*	ft_unset.c	*/
void	ft_unset(t_data *data, char **inputs, int i);
void	ft_unset_export(t_data *data, char **inputs, int i);
void	ft_unset_env(t_data *data, char **inputs, int i);

/*	ft_utils.c */
char	*ft_init_prompt(void);

#endif
