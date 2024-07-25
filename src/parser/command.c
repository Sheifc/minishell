#include "command.h"

// Función para crear un nodo de comando
Command	*create_command(const char *name, int fdin, int fdout, NodeType ope)
{
	Command	*cmd;

	cmd = (Command *)malloc(sizeof(Command));
	if (!cmd)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	cmd->name = ft_strdup(name);
	if (!cmd->name)
	{
		perror("strdup");
		free(cmd);
		exit(EXIT_FAILURE);
	}
	cmd->arg = NULL;
	cmd->n_args = 0;
	cmd->fdin = fdin;
	cmd->fdout = fdout;
	cmd->operator = ope;
	cmd->next = NULL;
	add_argument(cmd, name);
	return (cmd);
}

Command	*create_command_from_ast(ASTNode *node, int fdin, int fdout, NodeType ope)
{
	Command	*cmd;
	ASTNode	*arg_node;

	cmd = create_command(node->value, fdin, fdout, ope);
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
// int	execute_operator(ASTNode *node, int input_fd, int output_fd)
// {
// 	int	left_result;
// 	int	pipe_fds[2];

// 	if (node->type == NODE_PIPE)
// 	{
// 		if (pipe(pipe_fds) == -1)
// 		{
// 			perror("pipe");
// 			exit(EXIT_FAILURE);
// 		}
// 	}
// 	else if (node->type != NODE_PIPE)
// 	{
// 		printf("   left: %s\n", node->left->value);
// 		left_result = 1;
// 		// left_result = traverse_ast(node->left, input_fd, output_fd, NULL);
// 	}
// 	printf("%s\n", node->value);
// 	if (node->type == NODE_AND)
// 		return (handle_and(node, input_fd, output_fd, left_result));
// 	else if (node->type == NODE_OR)
// 		return (handle_or(node, input_fd, output_fd, left_result));
// 	else if (node->type == NODE_PARENTHESIS)
// 		return (handle_parenthesis(node, left_result));
// 	else if (node->type == NODE_PIPE)
// 		return (handle_pipe(node, input_fd, output_fd));
// 	else if (node->type == NODE_REDIRECT)
// 		return (handle_redirections(node, &input_fd, &output_fd));
// 	else
// 		return (-1);
// }

// int	execute_operator2(ASTNode *node, int input_fd, int output_fd)
// {
// 	int	left_result;
// 	int	pipe_fds[2];

// 	if (node->type == NODE_PIPE)
// 	{
// 		if (pipe(pipe_fds) == -1)
// 		{
// 			perror("pipe");
// 			exit(EXIT_FAILURE);
// 		}
// 	}
// 	else if (node->type != NODE_PIPE)
// 	{
// 		printf("   left: %s\n", node->left->value);
// 		left_result = 1;
// 		// left_result = traverse_ast(node->left, input_fd, output_fd, NULL);
// 	}
// 	printf("%s\n", node->value);
// 	if (node->type == NODE_AND)
// 		return (handle_and(node, input_fd, output_fd, left_result));
// 	else if (node->type == NODE_OR)
// 		return (handle_or(node, input_fd, output_fd, left_result));
// 	else if (node->type == NODE_PARENTHESIS)
// 		return (handle_parenthesis(node, left_result));
// 	else if (node->type == NODE_PIPE)
// 		return (handle_pipe(node, input_fd, output_fd));
// 	else if (node->type == NODE_REDIRECT)
// 		return (handle_redirections(node, &input_fd, &output_fd));
// 	else
// 		return (-1);
// }

// Main function
// Command	*traverse_ast(ASTNode *node, int input_fd, int output_fd, NodeType *ope)
// {
// 	Command *head = NULL;
//     Command *tail = NULL;
// 	Command	*cmd;

// 	// printf(" * %s*\n", node->value);
// 	if (node == NULL)
// 		return (NULL);
// 	// if (node->type == NODE_PIPE || node->type == NODE_AND
// 	// 	|| node->type == NODE_OR || node->type == NODE_PARENTHESIS
// 	// 	|| node->type == NODE_REDIRECT)
// 	// 	return (execute_operator(node, input_fd, output_fd));
// 	else if (node->type == NODE_COMMAND)
// 	{
// 		cmd = create_command_from_ast(node, input_fd, output_fd, ope);
// 		print_command(cmd);
// 		if (cmd) {
// 			if (head == NULL) {
// 				head = tail = cmd;
// 			} else {
// 				tail->next = cmd;
// 			}
// 			while (tail->next) {
// 				tail = tail->next;
// 			}
// 		}
// 		return (head);
// 	}
// 	else if (node->type == NODE_PIPE)
// 	{
// 		int pipe_fds[2];
// 		pipe(pipe_fds);
// 		printf(" pipes: %d, %d\n", pipe_fds[READ], pipe_fds[WRITE]);
// 		Command *left_cmds = traverse_ast(node->left, input_fd, pipe_fds[WRITE], &node->type);
// 		Command *right_cmds = traverse_ast(node->right, pipe_fds[READ], output_fd, &node->type);
// 		if (left_cmds) {
// 			if (head == NULL) {
// 				head = tail = left_cmds;
// 			} else {
// 				tail->next = left_cmds;
// 			}
// 			while (tail->next) {
// 				tail = tail->next;
// 			}
// 		}
// 		if (right_cmds) {
// 			if (head == NULL) {
// 				head = tail = right_cmds;
// 			} else {
// 				tail->next = right_cmds;
// 			}
// 			while (tail->next) {
// 				tail = tail->next;
// 			}
// 		}
// 	}
// 	else if (node->type == NODE_REDIRECT)
// 	{
// 		int fd = open(node->right->value, O_WRONLY | O_CREAT | O_TRUNC, 0644);
// 		Command *left_cmds = traverse_ast(node->left, input_fd, output_fd, &node->type);
// 		Command *right_cmds = traverse_ast(node->right, input_fd, fd, &node->type);
// 		if (left_cmds) {
// 			if (head == NULL) {
// 				head = tail = left_cmds;
// 			} else {
// 				tail->next = left_cmds;
// 			}
// 			while (tail->next) {
// 				tail = tail->next;
// 			}
// 		}
// 		if (right_cmds) {
// 			if (head == NULL) {
// 				head = tail = right_cmds;
// 			} else {
// 				tail->next = right_cmds;
// 			}
// 			while (tail->next) {
// 				tail = tail->next;
// 			}
// 		}
// 	}
// 	else
// 	{
// 		Command *left_cmds = traverse_ast(node->left, input_fd, output_fd, &node->type);
// 		Command *right_cmds = traverse_ast(node->right, input_fd, output_fd, &node->type);
// 		if (left_cmds) {
// 			if (head == NULL) {
// 				head = tail = left_cmds;
// 			} else {
// 				tail->next = left_cmds;
// 			}
// 			while (tail->next) {
// 				tail = tail->next;
// 			}
// 		}
// 		if (right_cmds) {
// 			if (head == NULL) {
// 				head = tail = right_cmds;
// 			} else {
// 				tail->next = right_cmds;
// 			}
// 			while (tail->next) {
// 				tail = tail->next;
// 			}
// 		}
// 	}
// 	return (head);
// }

void push_operator(OperatorStack **stack, NodeType type) {
    OperatorStack *new_node = (OperatorStack *)malloc(sizeof(OperatorStack));
    new_node->type = type;
    new_node->next = *stack;
    *stack = new_node;
}

NodeType pop_operator(OperatorStack **stack) {
    if (*stack == NULL) {
        return NODE_END;
    }
    OperatorStack *top = *stack;
    NodeType type = top->type;
    *stack = top->next;
    free(top);
    return type;
}

NodeType peek_operator(OperatorStack *stack) {
    if (stack == NULL) {
        return NODE_END;
    }
    return stack->type;
}

Command *traverse_ast(ASTNode *node, int input_fd, int output_fd, OperatorStack **ope_stack) {
    Command *head = NULL;
    Command *tail = NULL;
    Command *cmd;

    if (node == NULL)
        return NULL;
    
    if (node->type == NODE_COMMAND) {
        NodeType parent_ope = peek_operator(*ope_stack);	
        cmd = create_command_from_ast(node, input_fd, output_fd, parent_ope);
		print_command(cmd);
		pop_operator(ope_stack);
        return cmd;
    }
	else if (node->type == NODE_PIPE)
	{
        push_operator(ope_stack, node->type);
        if (node->type == NODE_PIPE) {
            int pipe_fds[2];
            pipe(pipe_fds);
            printf(" \e[1;36mpipes: (W)%d => (R)%d\e[0m\n", pipe_fds[WRITE], pipe_fds[READ]);
            Command *left_cmds = traverse_ast(node->left, input_fd, pipe_fds[1], ope_stack);
            Command *right_cmds = traverse_ast(node->right, pipe_fds[0], output_fd, ope_stack);
            if (left_cmds) {
				if (head == NULL) {
					head = tail = left_cmds;
				} else {
					tail->next = left_cmds;
				}
				while (tail->next) {
					tail = tail->next;
				}
			}
			if (right_cmds) {
				if (head == NULL) {
					head = tail = right_cmds;
				} else {
					tail->next = right_cmds;
				}
				while (tail->next) {
					tail = tail->next;
				}
			}
        }
	}
	else if (node->type == NODE_OUTPUT || node->type == NODE_OUTPUT_APPEND)
	{
        push_operator(ope_stack, node->type);
		int fd = output_fd;
		if (ft_strncmp(node->value, ">>", 2)==0) {
			fd = open(node->right->left->value, O_WRONLY | O_CREAT | O_APPEND, 0644);
		} else if (ft_strncmp(node->value, ">", 1)==0) {
			fd = open(node->right->left->value, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		}
		printf(" \e[1;36mfile: (W)%d\e[0m\n", fd);
		Command *left_cmds = traverse_ast(node->left, input_fd, fd, ope_stack);
		Command *right_cmds = traverse_ast(node->right, input_fd, output_fd, ope_stack);
		if (left_cmds) {
			if (head == NULL) {
				head = tail = left_cmds;
			} else {
				tail->next = left_cmds;
			}
			while (tail->next) {
				tail = tail->next;
			}
		}
		if (right_cmds) {
			if (head == NULL) {
				head = tail = right_cmds;
			} else {
				tail->next = right_cmds;
			}
			while (tail->next) {
				tail = tail->next;
			}
		}
	}
	else if (node->type == NODE_AND || node->type == NODE_OR)
	{
        push_operator(ope_stack, node->type);
		Command *left_cmds = traverse_ast(node->left, input_fd, output_fd, ope_stack);
		Command *right_cmds = traverse_ast(node->right, input_fd, output_fd, ope_stack);
		if (left_cmds) {
			if (head == NULL) {
				head = tail = left_cmds;
			} else {
				tail->next = left_cmds;
			}
			while (tail->next) {
				tail = tail->next;
			}
		}
		if (right_cmds) {
			if (head == NULL) {
				head = tail = right_cmds;
			} else {
				tail->next = right_cmds;
			}
			while (tail->next) {
				tail = tail->next;
			}
		}
	}
	else if (node->type == NODE_PARENTHESIS)
	{
        push_operator(ope_stack, node->type);
		Command *left_cmds = traverse_ast(node->left, input_fd, output_fd, ope_stack);
		if (left_cmds) {
			if (head == NULL) {
				head = tail = left_cmds;
			} else {
				tail->next = left_cmds;
			}
			while (tail->next) {
				tail = tail->next;
			}
		}
	}
    
	// else {
    //     // Handle other node types as needed
    //     traverse_ast(node->left, input_fd, output_fd, ope_stack);
    //     traverse_ast(node->right, input_fd, output_fd, ope_stack);
    // }

    return head;
}
