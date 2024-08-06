#ifndef COMMAND_H
# define COMMAND_H

# include "ast.h"
# include "libft.h"
# include "stacks.h"
# include "syntax.h"
# include <fcntl.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include "structures.h"

# define READ 0
# define WRITE 1
# define CMD_BUFFER_SIZE 4096

typedef struct _Fds
{
	int			in;
	int			out;
}				Fds;

/* typedef struct _cmd
{
	char		*name;
	char		**arg;
	int			n_args;
	int			fdin;
	int			fdout;
	struct _cmd	*prev;
	struct _cmd	*next;
	NodeType	operator;
}				t_cmd; */

// Command
void			postprocess_cmds(t_cmd *cmd);
t_cmd			*traverse_ast(ASTNode *node, Fds fds, OperatorStack **ope_stack,
					PipeStack **pipe_stack);

// Command utils
void			print_fd_contents(int fd);
void			add_argument(t_cmd *cmd, const char *arg);
char			**build_cmd_args(t_cmd *cmd);
void			free_commands(t_cmd **head);
void			print_command(t_cmd *cmd);

// Command handles1
t_cmd			*handle_node_command(ASTNode *node, Fds fds,
					OperatorStack **ope_stack);
t_cmd			*handle_node_pipe(ASTNode *node, Fds fds,
					OperatorStack **ope_stack, PipeStack **pipe_stack);
t_cmd			*handle_node_output(ASTNode *node, Fds fds,
					OperatorStack **ope_stack, PipeStack **pipe_stack);
t_cmd			*handle_node_input(ASTNode *node, Fds fds,
					OperatorStack **ope_stack, PipeStack **pipe_stack);
t_cmd			*handle_node_heredoc(ASTNode *node, Fds fds,
					OperatorStack **ope_stack, PipeStack **pipe_stack);

// Command handles2
t_cmd			*create_command(const char *name, Fds fds, NodeType ope);
t_cmd			*create_command_from_ast(ASTNode *node, Fds fds, NodeType ope);
void			append_commands(t_cmd **head, t_cmd **tail, t_cmd *new_cmds);
t_cmd			*handle_node_and_or_semicolon(ASTNode *node, Fds fds,
					OperatorStack **ope_stack, PipeStack **pipe_stack);
t_cmd			*handle_node_parenthesis(ASTNode *node, Fds fds,
					OperatorStack **ope_stack, PipeStack **pipe_stack);

// Command exe
int				execute_command(t_cmd *cmd, int input_fd, int output_fd);
pid_t			create_child_process(void);
void			setup_child_process(t_cmd *cmd, int input_fd, int output_fd,
					int pipe_fds[2]);
void			handle_parent_process(pid_t pid, int pipe_fds[2], int *status);
void			setup_redirections(int input_fd, int output_fd,
					int pipe_write_fd);

// Command extra
Token			**tokenize_input(t_shell *data);
ASTNode			*create_ast(t_shell *data);
bool			validate_and_free_tokens(t_shell *data);
t_cmd			*generate_commands(ASTNode *ast, bool is_valid, Fds fds);
void			print_commands(t_cmd *cmd);

#endif
