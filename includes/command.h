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
	int		input_fd;
	int		output_fd;
}			Command;

// Command
Command		*create_command(const char *name);
int			traverse_ast(ASTNode *node);
int			execute_operator(ASTNode *node);

// Command utils
void		print_fd_contents(int fd);
void		add_argument(Command *cmd, const char *arg);
char		**build_cmd_args(Command *cmd);
void		free_command(Command *cmd);
void		print_command(Command *cmd);

#endif
