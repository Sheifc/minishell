#include "command.h"

// Función para crear un nodo de comando
Command	*create_command(const char *name)
{
	Command	*cmd;

	cmd = malloc(sizeof(Command));
	if (!cmd)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	cmd->name = strdup(name);
	if (!cmd->name)
	{
		perror("strdup");
		free(cmd);
		exit(EXIT_FAILURE);
	}
	cmd->args = NULL;
	cmd->arg_count = 0;
	return (cmd);
}

Command	*create_command_from_ast(ASTNode *node)
{
	Command	*cmd;
	ASTNode	*arg_node;

	cmd = create_command(node->value);
	arg_node = node->left;
	cmd = create_command(node->value);
	arg_node = node->left;
	while (arg_node)
	{
		if (arg_node->type == NODE_ARGUMENT)
			add_argument(cmd, arg_node->value);
		arg_node = arg_node->left;
	}
	return (cmd);
}

// Función para manejar la ejecución de operadores
int	execute_operator(ASTNode *node, int input_fd, int output_fd)
{
	int	left_result;
	int	pipe_fds[2];

	if (node->type == NODE_PIPE) 
	{
		if (pipe(pipe_fds) == -1)
		{
			perror("pipe");
			exit(EXIT_FAILURE);
		}
		left_result = traverse_ast(node->left, input_fd, pipe_fds[1]);
	}
	else
		left_result = traverse_ast(node->left, input_fd, output_fd);
	printf("%s\n", node->value);
	if (node->type == NODE_AND)
		return (handle_and(node, input_fd, output_fd, left_result));
	else if (node->type == NODE_OR)
		return (handle_or(node, input_fd, output_fd, left_result));
	else if (node->type == NODE_PARENTHESIS)
		return (handle_parenthesis(node, left_result));
	else if (node->type == NODE_PIPE)
		return (handle_pipe(node, input_fd, output_fd));
	else
		return (-1);
}

// Main function
int	traverse_ast(ASTNode *node, int input_fd, int output_fd)
{
	Command	*cmd;
	int		result;

	if (node == NULL)
		return (-1);
	if (node->type == NODE_PIPE || node->type == NODE_AND
		|| node->type == NODE_OR || node->type == NODE_PARENTHESIS)
		return (execute_operator(node, input_fd, output_fd));
	else if (node->type == NODE_COMMAND)
	{
		cmd = create_command_from_ast(node);
		print_command(cmd);
		result = execute_command(cmd, input_fd, output_fd);
		free_command(cmd);
		return (result);
	}
	traverse_ast(node->left, input_fd, output_fd);
	traverse_ast(node->right, input_fd, output_fd);
	return (0);
}
