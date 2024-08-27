/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sheferna <sheferna@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 19:19:00 by sheferna          #+#    #+#             */
/*   Updated: 2024/08/27 18:50:26 by sheferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "command.h"
# include "structures.h"
# include "syntax.h"
# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <unistd.h>

//*--------------------INIT------------------------------------------
void		init(t_shell *data, char **envp);
int			only_spaces(char *prompt);
int			only_wildcard(char *prompt);
void		init_shell(t_shell *data, char **envp);

//*--------------------SIGNALS---------------------------------------
extern int	g_sig;

void		heredoc_handler(int signum);
void		sigint_handler(int signum);
void		signal_d(t_shell *data);
void		signal_quit(int signal);
void		sigchld_handler(int signum);
void		init_signals(void);

//*--------------------BUILTINS--------------------------------------
int			execute_builtin(t_shell *data, t_cmd *cmd, char *arg);

//*--------------------CD--------------------------------------------
t_env		*env_lst_search(t_env *env, const char *key);
char		*get_cd_value(t_env *env, const char *key);
int			multiple_args(t_shell *data, t_cmd *cmd);
char		*get_pwd(t_shell *data, t_cmd *cmd, char *path);
int			ft_chdir(t_shell *data, char *pwd);
char		*go_to(t_shell *data, char *location, char *error);
int			update_variables(char *new_pwd, char *old_pwd, t_env *list);
void		ft_cd(t_shell *data, t_cmd *cmd);

//*--------------------ECHO------------------------------------------
void		ft_echo(t_shell *data, t_cmd *cmd);

//*--------------------ENV-------------------------------------------
void		handle_env_other_errors(char *arg, t_shell *data);
void		handle_env_error(char *arg, t_shell *data);
void		fill_env_list(t_env **head, char **envp, int *i);
void		init_env(t_shell *data, char **envp);
void		print_env(t_env *env);
void		ft_env(t_shell *data, t_env *env);

//*--------------------EXPORT----------------------------------------
int			is_valid(t_shell *data);
t_env		*new_node(int i);
void		addback_node(t_env **export, t_env *aux);
void		print_export(t_shell *data);
t_env		*new_node(int i);
void		ft_swap(char **a, char **b);
void		ft_export(t_shell *data, t_cmd *cmd);

//*--------------------EXIT------------------------------------------
void		ft_exit(t_shell *data, t_cmd *cmd);

//*--------------------PWD-------------------------------------------
char		*get_current_directory(t_shell *data);
void		ft_pwd(t_shell *data);

//*--------------------UNSET-----------------------------------------
void		ft_unset(t_shell *data);

//*--------------------UTILS-----------------------------------------
void		add(t_env **head, char *key, char *value);
void		pop(t_env **head, char *key);
t_cmd		*get_last_cmd(t_cmd *cmd);
void		get_key_value(char *str, char **key, char **value);
char		*get_value(t_env *env, const char *key);
void		update_status(t_shell *data);
void		ft_error_cmd(t_cmd *cmd);

//*--------------------CHECKER---------------------------------------
int			is_invalid_ampersand(char *arg);
int			is_invalid_dot_usage(char *arg);
int			is_special_char(char c);
int			checker(t_shell *data, t_cmd *cmd);

//*--------------------EXECUTOR--------------------------------------

void		set_tmp_fds(t_shell *data);
void		dup_fdin_tmp(t_shell *data, t_cmd *cmd);
void		restart_fds(t_shell *data);
void		executor(t_shell *data);

void		run_single_cmd(t_shell *data, t_cmd *cmd);
void		exec_pipe(t_shell *data, t_cmd *cmd);
void		exec_multiple_cmds(t_shell *data, t_cmd *cmd);

void		fdin(t_cmd *cmd);
void		fdout(t_cmd *cmd);
void		set_up_fds(t_cmd *cmd);
void		exec_one_cmd(t_shell *data, t_cmd *cmd);

void		run_cmd(t_shell *data, t_cmd *cmd);
void		redir_fdin(t_shell *data, t_cmd *cmd);
void		redir_fdout(t_shell *data, t_cmd *cmd);
void		exec_redir(t_shell *data, t_cmd *cmd);

//*--------------------EXECUTOR BONUS--------------------------------
void		exec_node_or(t_shell *data, t_cmd *cmd, int *execution);
void		exec_node_and(t_shell *data, t_cmd *cmd, int *execution);
void		exec_bonus(t_shell *data, t_cmd *cmd, int *execution);
void		update_total_status(t_shell *data);
void		parenthesis_open(t_shell *data, t_cmd **cmd, int *execution);
void		parenthesis_close(t_shell *data, t_cmd **cmd, int *execution);
void		none_parenthesis(t_shell *data, t_cmd **cmd, int *execution);
void		exec_parenthesis(t_shell *data, t_cmd *cmd, int *execution);

//*--------------------EXECUTOR UTILS--------------------------------

void		get_path(t_shell *data, t_cmd *cmd);
void		count_commands(t_shell *data);
void		get_status(t_shell *data);
void		wait_process(t_shell *data);
void		save_pipe(int *fdpipe);
pid_t		saved_fork(void);
pid_t		save_fork(t_shell *data);
void		wait_pid(pid_t pid, t_shell *data);

//*--------------------PRINTING--------------------------------------

void		print_key(t_env *head);
char		*print_value(t_env *env, char *key);
void		print_list(t_env *head);
void		print_argu(char **args);

//*--------------------FREE------------------------------------------

void		free_env_list(t_env *head);
void		free_env_node(t_env **node);

void		free_pwd(char *old_pwd, char *new_pwd);

void		free_arg(char ***matrix);
void		free_cmd(t_cmd **cmd);
void		free_cmd_list(t_cmd **cmd_list);

void		free_all(t_shell *data);

//*--------------------ERROR-----------------------------------------

void		ft_perror_exit(char *str, t_shell *data);
void		ft_error_cmd(t_cmd *cmd);

#endif