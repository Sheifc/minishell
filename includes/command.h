/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sheferna <sheferna@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 18:49:47 by sheferna          #+#    #+#             */
/*   Updated: 2024/08/27 18:49:48 by sheferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMAND_H
# define COMMAND_H

# include "ast.h"
# include "libft.h"
# include "stacks.h"
# include "structures.h"
# include "syntax.h"
# include <fcntl.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# define READ 0
# define WRITE 1
# define CMD_BUFFER_SIZE 4096

typedef struct s_fds
{
	int					in;
	int					out;
}						t_fds;

typedef struct s_cmd_arg
{
	t_ast_node			*node;
	t_fds				fds;
	t_operator_stack	**ope_stack;
	t_pipe_stack		**pipe_stack;
	bool				open_parenthesis;
}						t_cmd_arg;

// Command
void					postprocess_cmds(t_shell *data);
t_cmd					*traverse_ast(t_cmd_arg *arg, t_shell *data);

// Command utils
void					print_fd_contents(int fd);
void					add_argument(t_cmd *cmd, const char *arg,
							t_shell *data);
char					**build_cmd_args(t_cmd *cmd);
void					free_commands(t_cmd **head);
void					print_command(t_cmd *cmd);

// Command handles1
void					handle_parenthesis_status(t_cmd *cmd, t_cmd_arg *arg);
t_cmd					*handle_node_command(t_cmd_arg *arg, t_shell *data);
t_cmd					*handle_node_output(t_cmd_arg *arg, t_shell *data);
t_cmd					*handle_node_input(t_cmd_arg *arg, t_shell *data);
t_cmd					*handle_node_heredoc(t_cmd_arg *arg, t_shell *data);

// Command handles2
t_cmd					*create_command(t_cmd_arg *arg, t_shell *data);
t_cmd					*create_command_from_ast(t_cmd_arg *arg, t_shell *data);
void					append_commands(t_cmd **head, t_cmd **tail,
							t_cmd *new_cmds);
t_cmd					*handle_node_and_or_semicolon(t_cmd_arg *arg,
							t_shell *data);
t_cmd					*handle_node_parenthesis(t_cmd_arg *arg, t_shell *data);

// Command handles utils
void					delete_command(t_cmd **node, t_cmd **head);
char					*read_until_eof(char *line, char *eof, char *result);
void					ft_read_stdin(int fd, char *eof, t_shell *data);
t_cmd					*process_node_commands(t_cmd_arg *arg, t_shell *data,
							int fd, t_redirect dir);

// Command exe
int						execute_command(t_cmd *cmd, int input_fd,
							int output_fd);
pid_t					create_child_process(void);
void					setup_child_process(t_cmd *cmd, int input_fd,
							int output_fd, int pipe_fds[2]);
void					handle_parent_process(pid_t pid, int pipe_fds[2],
							int *status);
void					setup_redirections(int input_fd, int output_fd,
							int pipe_write_fd);

// Command extra
t_token					**tokenize_input(t_shell *data);
t_ast_node				*create_ast(t_shell *data);
bool					validate_and_free_tokens(t_shell *data);
t_cmd					*generate_commands(t_shell *data, bool is_valid,
							t_fds fds);
void					print_commands(t_cmd *cmd);

#endif
