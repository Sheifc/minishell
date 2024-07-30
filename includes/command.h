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

# define READ 0
# define WRITE 1
# define CMD_BUFFER_SIZE 4096

typedef struct _Fds
{
	int				in;
	int				out;
}					Fds;

typedef struct _Command
{
	char			*name;
	char			**arg;
	int				n_args;
	int				fdin;
	int				fdout;
	struct _Command	*prev;
	struct _Command	*next;
	NodeType		operator;
}					Command;

// Command
Command				*traverse_ast(ASTNode *node, Fds fds,
						OperatorStack **ope_stack, PipeStack **pipe_stack);

// Command utils
void				print_fd_contents(int fd);
void				add_argument(Command *cmd, const char *arg);
char				**build_cmd_args(Command *cmd);
void				free_commands(Command **head);
void				print_command(Command *cmd);

// Command handles1
Command				*handle_node_command(ASTNode *node, Fds fds,
						OperatorStack **ope_stack);
Command				*handle_node_pipe(ASTNode *node, Fds fds,
						OperatorStack **ope_stack, PipeStack **pipe_stack);
Command				*handle_node_output(ASTNode *node, Fds fds,
						OperatorStack **ope_stack, PipeStack **pipe_stack);
Command				*handle_node_input(ASTNode *node, Fds fds,
						OperatorStack **ope_stack, PipeStack **pipe_stack);
Command				*handle_node_heredoc(ASTNode *node, Fds fds,
						OperatorStack **ope_stack, PipeStack **pipe_stack);

// Command handles2
Command				*create_command(const char *name, Fds fds, NodeType ope);
Command				*create_command_from_ast(ASTNode *node, Fds fds,
						NodeType ope);
void				append_commands(Command **head, Command **tail,
						Command *new_cmds);
Command				*handle_node_and_or_semicolon(ASTNode *node, Fds fds,
						OperatorStack **ope_stack, PipeStack **pipe_stack);
Command				*handle_node_parenthesis(ASTNode *node, Fds fds,
						OperatorStack **ope_stack, PipeStack **pipe_stack);

// Command exe
int					execute_command(Command *cmd, int input_fd, int output_fd);
pid_t				create_child_process(void);
void				setup_child_process(Command *cmd, int input_fd,
						int output_fd, int pipe_fds[2]);
void				handle_parent_process(pid_t pid, int pipe_fds[2],
						int *status);
void				setup_redirections(int input_fd, int output_fd,
						int pipe_write_fd);

// Command extra
Token				**tokenize_input(const char *input, int *num_tokens);
ASTNode				*create_ast(Token **tokens, int num_tokens);
bool				validate_and_free_tokens(Token **tokens, int *num_tokens,
						ASTNode *ast);
Command				*generate_commands(ASTNode *ast, bool is_valid, Fds fds);
void				print_commands(Command *cmd);

#endif
