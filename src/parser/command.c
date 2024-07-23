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
	// int pipe_fds[2];
	// if (pipe(pipe_fds) == -1)
	// {
	//     perror("pipe");
	//     free(cmd->name);
	//     free(cmd);
	//     exit(EXIT_FAILURE);
	// }
	// cmd->input_fd = pipe_fds[READ];
	// cmd->output_fd = pipe_fds[WRITE];
	cmd->input_fd = -1;
	cmd->output_fd = -1;
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

// Ejecución de comando
int	execute_command(Command *cmd)
{
	int		pipe_fds[2];
	pid_t	pid;
	int		status;

	printf(" - Ejecutando comando: \e[33m%s\e[0m -\n", cmd->name);
	pipe(pipe_fds);
	pid = fork();
	if (pid == 0)
	{
		if (cmd->input_fd != -1)
		{
			dup2(cmd->input_fd, STDIN_FILENO);
			close(cmd->input_fd);
		}
		if (cmd->output_fd != -1)
		{
			dup2(cmd->output_fd, STDOUT_FILENO);
			close(cmd->output_fd);
		}
		else
			dup2(pipe_fds[WRITE], STDOUT_FILENO);
		close(pipe_fds[READ]);
		close(pipe_fds[WRITE]);
		execvp(cmd->name, build_cmd_args(cmd));
		perror("execvp");
		exit(EXIT_FAILURE);
	}
	else if (pid < 0)
	{
		perror("fork");
		return (-1);
	}
	close(pipe_fds[WRITE]);
	waitpid(pid, &status, 0);
	print_fd_contents(pipe_fds[READ]);
	close(pipe_fds[READ]);
	printf(" ------------------------------\n");
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (-1);
}

// Función para manejar la ejecución de operadores
int	execute_operator(ASTNode *node)
{
	int	pipe_fds[2];
	int	left_result;
	int	right_result;

	left_result = -1;
	right_result = -1;
	if (node->type == NODE_PIPE)
	{
		if (pipe(pipe_fds) == -1)
		{
			perror("pipe");
			exit(EXIT_FAILURE);
		}
	}
	left_result = traverse_ast(node->left);
	printf("%s\n", node->value);
	if (node->type == NODE_AND)
	{
		printf(" * (AND) result left: %d\n", left_result);
		if (left_result == 0)
		{
			right_result = traverse_ast(node->right);
			return (right_result);
		}
		return (left_result);
	}
	else if (node->type == NODE_OR)
	{
		printf(" * (OR) result left: %d\n", left_result);
		if (left_result != 0)
		{
			right_result = traverse_ast(node->right);
			return (right_result);
		}
		return (left_result);
	}
	else if (node->type == NODE_PARENTHESIS)
	{
		if (node->left)
			return (left_result);
		return (-1);
	}
	else if (node->type == NODE_PIPE)
	{
		if (left_result != -1)
		{
			close(pipe_fds[READ]);
			if (dup2(pipe_fds[WRITE], STDOUT_FILENO) == -1)
			{
				perror("dup2");
				exit(EXIT_FAILURE);
			}
			close(pipe_fds[WRITE]);
		}
		right_result = traverse_ast(node->right);
		if (right_result != -1)
		{
			close(pipe_fds[WRITE]);
			if (dup2(pipe_fds[READ], STDIN_FILENO) == -1)
			{
				perror("dup2");
				exit(EXIT_FAILURE);
			}
			close(pipe_fds[READ]);
		}
		return (right_result);
	}
	return (-1);
}

// Main function
int	traverse_ast(ASTNode *node)
{
	Command	*cmd;
	int		result;

	if (node == NULL)
	{
		return (-1);
	}
	if (node->type == NODE_PIPE || node->type == NODE_AND
		|| node->type == NODE_OR || node->type == NODE_PARENTHESIS)
	{
		return (execute_operator(node));
	}
	else if (node->type == NODE_COMMAND)
	{
		cmd = create_command_from_ast(node);
		print_command(cmd);
		result = execute_command(cmd);
		free_command(cmd);
		return (result);
	}
	traverse_ast(node->left);
	traverse_ast(node->right);
	return (0);
}
