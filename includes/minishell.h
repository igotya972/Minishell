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

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <signal.h>
# include <string.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/libft.h"
# include <fcntl.h>
# include <errno.h>
# include <stdbool.h>
# include <stdarg.h>
# include <stddef.h>
# include <sys/wait.h>
# include <sys/types.h>

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

/*	ft_signal.c	*/
void	signal_manager(int signum);
void	handle_ctrld(t_data *data);

/*	minishell.c	*/
void	minishell_prompt(t_data *data);

/*	exec_cmd.c	*/
void	exec_cmd(t_data *data);

/*	parser.c	*/
void	lexer(t_data *data);
char	*ft_space_to_control(char *input);
int		ft_is_in_quotes(char *input, int i);
char	*ft_del_quote(char *input);
void	lexer_temporaire(t_data *data);
char	*ft_var_to_value(char *input, t_data *data);
char	*ft_replace_var(char *input, int i, t_data *data, int *len_value);
char	*ft_del_key(char *input, int i);
char	*ft_add_to_str(char *input, char *value, int i, int len_key);
char	*ft_get_value(char *key, t_data *data);

/*	builtins.c	*/
int		ft_echo(t_data *data, char **inputs, int i);
void	launch_builtins(t_data *data, char **input);
void	ft_pwd(void);
void	launch_builtins2(t_data *data, char **inputs, int i);
void	ft_echo2(t_data *data, char **inputs, int *i, int *add);

/*	ft_cd.c		*/
void	ft_cd(t_data *data, char **inputs, int i);
void	export_modifier(t_data *data);
void	ft_chdir(t_data *data, char *path);

/*	init_data.c	*/
void	init_data(t_data *data, char **envp);
void	init_export(t_data *data);
char	*ft_keyinit(char *str);
char	*ft_valueinit(char *str);
char	*ft_export_str_init(char *key, char *value);
char	**init_envp(char **envp);

/*	free.c		*/
void	free_arguments(char **args);
void	ft_free(t_data *data);
void	ft_free_input_lexer(t_data *data);

/*	ft_export.c	*/
void	ft_export(t_data *data, char **inputs, int i, int flag);
void	ft_display_export(t_data *data);
void	export_add(t_data *data, char *key, char *value);
void	ft_sort_export(t_export *export);
char	*ft_value_with_quotation_mark(char *value);

/*	ft_unset.c	*/
void	ft_unset(t_data *data, char **inputs, int i);
void	ft_unset_export(t_data *data, char **inputs, int i);

/*	ft_utils.c */
char	*ft_init_prompt(void);

/*	ft_env.c	*/
void	ft_unset_env(t_data *data, char **inputs, int i);
void	envp_add(t_data *data, char *key, char *value);
char	**envp_modifier(t_data *data);
void	ft_env(t_data *data);

/*	path.c	*/
char	*path_cmd(char **path, char *cmd);

/*	ft_exit.c	*/
void	ft_error(char *str);
void	ft_exit(t_data *data);

/*	pipe.c	*/
int 	child_process(int *fd, char **argv, char **env);
int 	parent_process(int *fd, char **argv, char **env);

#endif
