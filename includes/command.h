#ifndef COMMAND_H
# define COMMAND_H

# include "ast.h"
# include "libft.h"
# include "syntax.h"
# include <fcntl.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# define READ 0
# define WRITE 1
# define CMD_BUFFER_SIZE 4096

typedef struct _Command
{
	char	*name;
	char	**args;
	int		arg_count;
}			Command;

// Command
Command		*create_command(const char *name);
int			traverse_ast(ASTNode *node, int input_fd, int output_fd);
int			execute_operator(ASTNode *node, int input_fd, int output_fd);

// Command utils
void		print_fd_contents(int fd);
void		add_argument(Command *cmd, const char *arg);
char		**build_cmd_args(Command *cmd);
void		free_command(Command *cmd);
void		print_command(Command *cmd);

// Command handles
int			handle_pipe(ASTNode *node, int input_fd, int output_fd);
int			handle_and(ASTNode *node, int input_fd, int output_fd,
				int left_result);
int			handle_or(ASTNode *node, int input_fd, int output_fd,
				int left_result);
int			handle_parenthesis(ASTNode *node, int left_result);
int			handle_redirections(ASTNode *node, int *input_fd, int *output_fd);

// Command exe
int			execute_command(Command *cmd, int input_fd, int output_fd);
pid_t		create_child_process(void);
void		setup_child_process(Command *cmd, int input_fd, int output_fd,
				int pipe_fds[2]);
void		handle_parent_process(pid_t pid, int pipe_fds[2], int *status);
void		setup_redirections(int input_fd, int output_fd, int pipe_write_fd);

#endif
