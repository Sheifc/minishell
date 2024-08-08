#ifndef MINISHELL_H
# define MINISHELL_H

# define RST "\033[0m"    /* Reset to default color */
# define RED "\033[1;31m" /* Bold Red */
# define G "\033[1;32m"   /* Bold Green */
# define Y "\033[1;33m"   /* Bold Yellow */
# define B "\033[1;34m"   /* Bold Blue */
# define M "\033[1;35m"   /* Bold Magenta */
# define C "\033[1;36m"   /* Bold Cyan */
# define W "\033[1;37m"   /* Bold White */

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

//*--------------------INIT--------------------------------
void		init(t_shell *data, char **envp);
int			only_spaces(char *prompt);
void		init_shell(t_shell *data, char **envp);

//*--------------------SIGNALS--------------------------------
extern int	g_sig;

void		sigint_handler(int signum);
void		signal_quit(int signal);
void		sigchld_handler(int signum);
void		init_signals(void);

//*--------------------BUILTINS----------------------------

// exec_builtins.c
int			execute_builtin(t_shell *data, t_cmd *cmd, char *arg);
void		run_single_cmd(t_shell *data, t_cmd *cmd);
void		get_status(t_shell *data);
// cd.c
t_env		*env_lst_search(t_env *env, const char *key);
void		ft_cd(t_shell *data, t_cmd *cmd);
// echo.c
void		ft_echo(t_shell *data, t_cmd *cmd);
// env.c
void		ft_env(t_shell *data, t_env *env);
// export.c
int			is_valid(t_shell *data);
t_env		*new_node(int i);
void		addback_node(t_env **export, t_env *aux);
void		print_export(t_shell *data);
t_env		*new_node(int i);
void		ft_export(t_shell *data, t_cmd *cmd);
// exit.c
void		ft_exit(t_cmd *cmd);
// pwd.c
char		*get_current_directory(void);
void		ft_pwd(t_shell *data);
// unset.c
void		ft_unset(t_shell *data);

//*--------------------ENV---------------------------------

// env.c
void		fill_env_list(t_env **head, char **envp, int *i);
void		init_env(t_shell *data, char **envp);
// list_utils.c
void		add(t_env **head, char *key, char *value);
void		pop(t_env **head, char *key);
t_cmd		*get_last_cmd(t_cmd *cmd);
// key_value.c
void		get_key_value(char *str, char **key, char **value);
char		*get_value(t_env *env, const char *key);
char		*get_cd_value(t_env *env, const char *key);

//*--------------------EXECUTOR----------------------------
void		get_path(t_shell *data, t_cmd *cmd);
void		set_tmp_fds(t_shell *data);
void		set_fdin(t_shell *data, t_cmd *cmd);
void		set_fdout(t_shell *data, t_cmd *cmd);
void		restart_fds(t_shell *data);
void		get_status(t_shell *data);

void		run_cmd(t_shell *data, t_cmd *cmd);
void		exec_multiple_cmds(t_shell *data, t_cmd *cmd);
void		exec_one_cmd(t_shell *data, t_cmd *cmd);
void		exec_redir(t_shell *data, t_cmd *cmd);
void		exec_pipe(t_shell *data, t_cmd *cmd);
void		executor(t_shell *data);

void		redir_to_infile_if_needed(t_cmd *cmd);
void		redir_to_outfile_if_needed(t_cmd *cmd);

//*--------------------EXECUTOR BONUS----------------------
void		exec_node_or(t_shell *data, t_cmd **cmd);
void		exec_node_and(t_shell *data, t_cmd **cmd);
void		exec_bonus(t_shell *data, t_cmd **cmd);

//*--------------------UTILS-------------------------------
// exec_utils.c
void		ft_swap(char **a, char **b);
void		count_commands(t_shell *data);
void		init_pid(t_shell *data);
void		end_processess(int *pids, int len);
void		wait_process(t_shell *data);

// printing.c
void		print_key(t_env *head);
char		*print_value(t_env *env, char *key);
void		print_list(t_env *head);
void		print_argu(char **args);
void		print_cmds(t_cmd *cmd);

//*--------------------FREE--------------------------------
void		free_env_list(t_env *head);
void		free_env_node(t_env **node);

void		free_arg(char ***matrix);
void		free_cmd(t_cmd **cmd);
void		free_cmd_list(t_cmd **cmd_list);

void		free_all(t_shell *data);

#endif