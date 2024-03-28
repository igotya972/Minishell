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

extern int				g_error;

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
	char		**path;
	char		**lexer;
	char		**envp;
	char		*input;
	char		*env_path;
	char		*old_pwd;
	int			oldpwd_status;
	int			pid;
	t_export	*export;
};

typedef struct s_pipe_data
{
	int		fd[2];
	int		fd_in;
	int		i;
	t_data	*data;
}			t_pipe_data;

typedef struct s_cmd
{
	char	*cmd;
	char	**args;
}	t_cmd;

/*	ft_signal.c	*/
void		signal_manager(int signum);
void		handle_ctrld(t_data *data);
void		child_signal(int signum);
void		child_signal_heredoc(int signum);

/*	minishell.c	*/
void		minishell_prompt(t_data *data);

/*	exec_cmd.c	*/
void		launch_exec(t_data *data);
void		exec_cmd(t_data *data, int i);
void		no_command(char *str, char *path, char **cmd, int flag);
void		exec_child_cmd(t_data *data, char *path, char **cmd, int i);
char		*pre_exec(t_data *data, int i);

/*	exec.pipe.c	*/
void		exec_pipe(t_data *data);
pid_t		ft_fork(t_data *data);
void		exec_simple_cmd(t_data *data, char *path, char **cmd);
void		prepare_and_exec_cmd(char **cmd, t_data *data);

/*	heredoc.c	*/
char		**launch_heredoc(t_data *data, int i, int fd[2]);
void		end_heredoc(int fd[2]);
int			is_redirection(char *str);

/*	heredoc_input_file.c	*/
int			redirect_input(t_data *data, char **lexer);
int			redirect_input_rdonly(t_data *data, char *file);
void		read_and_write_to_pipe(int pipe_write_end, char *delimiter);
void		redirect_input_heredoc(t_data *data, char *delimiter);
void		fake_heredoc(char *delimiter);

/*	heredoc_output_file.c	*/
int			redirect_output(char **lexer);
int			redirect_output2(char *file, int type);
int			open_append_trunc(char *file, int type);

/*	del_redirect.c	*/
char		**del_redirect(char **lexer);

/*	utils_pipe.c	*/
int			parent_process(int *fd_in, int fd[2], int i, t_data *data);
void		child_process(t_data *data, int i, int fd[2], int fd_in);
void		dup_and_close(t_data *data, int in_fd, int out_fd);

/*	parser.c	*/
void		lexer(t_data *data);
char		*ft_space_to_control(char *input);
int			ft_is_in_quotes(char *input, int i);
char		*ft_del_quote(char *input);

/*	parser2.c	*/
char		*ft_get_value(char *key, t_data *data);
char		*ft_key_to_replace(char *input, int i, int i_base);
char		*ft_copy_value(t_data *data, int i);
void		ft_flag_dquote(int *flag, int *anti_start_quote);
void		ft_flag_squote(int *flag, int *anti_start_quote);

/*	parser3.c	*/
char		*ft_add_to_str(char *input, char *value, int i, int len_key);
char		*ft_replace_var(char *input, int i, t_data *data, int *len_value);
char		*ft_var_to_value(char *input, t_data *data);
char		*ft_delimiteur(char *input);
int			check_parse_error(char **input);

/*	parser4.c	*/
char		*ft_delimiteur_to_control(char *str);
char		*ft_addcontrol(char *str, int j, int flag);
char		*add_control_preli(char *tmp, char *s, int *j, int flag);

/*	builtins.c	*/
int			ft_echo(char **inputs, int i);
void		launch_builtins(t_data *data, char **input, int i);
void		ft_pwd(void);
void		launch_builtins2(t_data *data, char **inputs, int i);
void		ft_echo2(char **inputs, int *i, int *add);

/*	ft_cd.c		*/
void		ft_cd(t_data *data, char **inputs, int i, char *ctrl_rm);
void		export_modifier(t_data *data);
int			ft_chdir(t_data *data, char *path);
void		ft_cd_minus(t_data *data);

/*	init_data.c	*/
void		init_data(t_data *data, char **envp);
void		init_export(t_data *data);
char		*ft_keyinit(char *str);
char		*ft_valueinit(char *str);
char		**init_envp(char **envp);

/*	init_data2.c	*/
char		*ft_export_str_init(char *key, char *value);
char		*ft_export_str_init2(char *tmp_str2, char *value);

/*	free.c		*/
void		ft_free(t_data *data);
void		ft_free2(t_data *data);
void		ft_free_tab(char **tab);

/*	ft_export.c	*/
void		ft_export(t_data *data, char **inputs, int i, int flag);
void		ft_display_export(t_data *data);
void		export_add(t_data *data, char *key, char *value);
void		ft_sort_export(t_export *export);
char		*ft_value_with_quotation_mark(char *value);

/*	ft_export2.c	*/
void		ft_export2(t_data *data, char **inputs, int i, int flag);
void		ft_export3(char *str);
t_export	*ft_export_add3(t_data *data);
void		ft_export_add4(t_data *data, int i);
void		ft_export_add5(int *key_count, int *j, int *i);

/*	ft_export3.c	*/
void		ft_export_add2(t_data *data, t_export *tmp, int j);
t_export	*ft_export_add6(t_export *tmp, char *value, char *key, int *j);
t_export	*ft_export_add7(t_data *data, t_export *tmp, int *j, int *i);

/*	ft_unset.c	*/
void		ft_unset(t_data *data, char **inputs, int i);
void		ft_unset_export(t_data *data, char **inputs, int i);
t_export	*ft_export_add3(t_data *data);

/*	ft_unset2.c	*/
void		ft_unset2(t_data *data, t_export *tmp, int j);
t_export	*ft_unset3(t_data *data);

/*	utils.c */
char		*ft_init_prompt(void);
void		ft_protect_malloc(void *ptr);
int			is_builtins(char *lexer_i);
int			until_delimiteur(char **str, int i);
int			is_value_delimiteur(char c);

/*	utils2.c	*/
int			is_parser_delimiteur(char c);
int			nbr_parser_delimiteur(char *str);
int			is_exec_delimiteur(char *str);
void		debug_tab(char **tab);
char		**cmd_until_delimiteur(char **lexer, int i);

/*	utils3.c	*/
char		**ft_remove_control_tab(char **str);
char		*ft_remove_control(char *str);
int			ft_atoi_simple(char *str);
int			is_pipe(char **lexer);
void		no_path(char *str);

/*	utils4.c	*/
void		delimiteur_modifier(char *tmp, char *input, int *i, int *j);
int			check_parse_error2(char **input, char **delimiteur, int i, int j);
void		ft_add_history(char *input);
char		**ft_strdup_tab(char **tab);
int			nbr_redirect(char **lexer);

/*	utils5.c	*/
int			is_redirection_input(char **lexer, int i);
int			is_redirection_output(char **lexer, int i);

/*	ft_env.c	*/
void		ft_unset_env(t_data *data, char **inputs, int i);
void		envp_add(t_data *data, char *key, char *value);
char		**envp_modifier(t_data *data);
void		ft_env(t_data *data);
char		**envp_modifier2(t_data *data, int i);

/*	ft_env2.c	*/
char		*envp_add2(t_data *data, char *key, char *value);
void		ft_unset_env2(t_data *data, char **new_envp, int k);
void		envp_add3(t_data *data, char **new_envp, char *tmp, int j);

/*	path.c	*/
char		*path_cmd(char **path, char *cmd);
char		**init_path(char **envp);

/*	ft_exit.c	*/
void		ft_error(char *str, t_data *data);
void		ft_exit(t_data *data, int i);

#endif
