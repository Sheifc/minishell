#include "command.h"

// Función para crear un nodo de comando
Command	*create_command(const char *name, Fds fds, NodeType ope)
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
	cmd->fdin = fds.in;
	cmd->fdout = fds.out;
	cmd->operator = ope;
	cmd->next = NULL;
	add_argument(cmd, name);
	return (cmd);
}

Command	*create_command_from_ast(ASTNode *node, Fds fds, NodeType ope)
{
	Command	*cmd;
	ASTNode	*arg_node;

	cmd = create_command(node->value, fds, ope);
	arg_node = node->left;
	while (arg_node)
	{
		if (arg_node->type == NODE_ARGUMENT)
			add_argument(cmd, arg_node->value);
		arg_node = arg_node->left;
	}
	return (cmd);
}

void	print_ope_stack(OperatorStack *head){
	OperatorStack *current = head;
	printf("Operation stack:\n");
	while(current){
		printf("  - type: %s\n", nodeTypeToSymbol(current->type));
		current = current->next;
	}
}

void	print_pipe_stack(PipeStack *head){
	PipeStack *current = head;
	printf("Pipe stack:\n");
	while(current){
		printf("  - fd_in:%d, fd_out:%d\n", current->fdin, current->fdout);
		current = current->next;
	}
}

void	push_operator(OperatorStack **stack, NodeType type) {
	OperatorStack *new_node;
	new_node = (OperatorStack *)malloc(sizeof(OperatorStack));
	new_node->type = type;
	new_node->next = *stack;
	*stack = new_node;
}

void	push_pipe(PipeStack **stack, int fdin, int fdout) {
	PipeStack *new_node;
	new_node = (PipeStack *)malloc(sizeof(PipeStack));
	new_node->fdin = fdin;
	new_node->fdout = fdout;
	new_node->next = *stack;
	*stack = new_node;
}

NodeType	pop_operator(OperatorStack **stack) {
	OperatorStack *top;
	NodeType type;
	if (*stack == NULL)
		return (NODE_END);
	top = *stack;
	type = top->type;
	*stack = top->next;
	free(top);
	return (type);
}

PipeStack*	pop_pipe(PipeStack **stack) {
	PipeStack	*top;
	if (*stack == NULL)
		return (NULL);
	top = *stack;
	*stack = top->next;
	free(top);
	return (*stack);
}

NodeType	peek_operator(OperatorStack *stack) {
	if (stack == NULL)
		return (NODE_END);
	return stack->type;
}

PipeStack* peek_pipe(PipeStack *stack) {
	if (stack == NULL)
		return (NULL);
	return stack;
}

Command *traverse_ast(ASTNode *node, Fds fds, OperatorStack **ope_stack, PipeStack **pipe_stack) {
	Command *head = NULL;
	Command *tail = NULL;
	Command *cmd;

	if (node == NULL)
		return NULL;
	if (node->type == NODE_COMMAND) {
		NodeType parent_ope = peek_operator(*ope_stack);
		if (parent_ope == NODE_PARENTHESIS){
			pop_operator(ope_stack);
			parent_ope = peek_operator(*ope_stack);
		}
		cmd = create_command_from_ast(node, fds, parent_ope);
		// print_command(cmd);
		pop_operator(ope_stack);
		return cmd;
	}
	else if (node->type == NODE_PIPE)
	{
		push_operator(ope_stack, node->type);
		int pipe_fds[2];
		pipe(pipe_fds);
		printf(" \e[1;36mpipes: (W)%d => (R)%d\e[0m\n", pipe_fds[WRITE], pipe_fds[READ]);
		Command *left_cmds = traverse_ast(node->left, (Fds){fds.in, pipe_fds[WRITE]}, ope_stack, pipe_stack);
		Command *right_cmds = traverse_ast(node->right, (Fds){pipe_fds[READ], fds.out}, ope_stack, pipe_stack);
		if (left_cmds) {
			if (head == NULL) {
				head = tail = left_cmds;
			} else {
				tail->next = left_cmds;
				left_cmds->prev = tail;
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
				right_cmds->prev = tail;
			}
			while (tail->next) {
				tail = tail->next;
			}
		}
	}
	else if (node->type == NODE_OUTPUT || node->type == NODE_OUTPUT_APPEND)
	{
		push_operator(ope_stack, node->type);
		int fd = fds.out;
		if (ft_strncmp(node->value, ">>", 2) == 0) {
			fd = open(node->right->left->value, O_WRONLY | O_CREAT | O_APPEND, 0644);
		} else if (ft_strncmp(node->value, ">", 1) == 0) {
			fd = open(node->right->left->value, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		}
		push_pipe(pipe_stack, fds.in, fd);
		printf(" \e[1;36mfile: (W)%d\e[0m\n", fd);
		Command *left_cmds = traverse_ast(node->left, fds, ope_stack, pipe_stack);
		Command *right_cmds = traverse_ast(node->right, fds, ope_stack, pipe_stack);
		if (left_cmds) {
			if (head == NULL) {
				head = tail = left_cmds;
			} else {
				tail->next = left_cmds;
				left_cmds->prev = tail;
			}
			while (tail->next) {
				tail = tail->next;
			}
			tail->fdout = fd;
		}
		if (right_cmds) {
			if (head == NULL) {
				head = tail = right_cmds;
			} else {
				tail->next = right_cmds;
				right_cmds->prev = tail;
			}
			while (tail->next) {
				tail = tail->next;
			}
		}
	}
	else if (node->type == NODE_INPUT) {
		push_operator(ope_stack, node->type);
		fds.in = open(node->right->left->value, O_RDONLY);
		Command *left_cmds = traverse_ast(node->left, fds, ope_stack, pipe_stack);
		Command *right_cmds = traverse_ast(node->right, fds, ope_stack, pipe_stack);
		if (left_cmds) {
			if (head == NULL) {
				head = tail = left_cmds;
			} else {
				tail->next = left_cmds;
				left_cmds->prev = tail;
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
				right_cmds->prev = tail;
			}
			while (tail->next) {
				tail = tail->next;
			}
		}
	}
	else if (node->type == NODE_HEREDOC) {
		push_operator(ope_stack, node->type);
		int temp_fd = open("heredoc_temp", O_WRONLY | O_CREAT | O_TRUNC, 0644);
		write(temp_fd, node->right->left->value, strlen(node->right->left->value));
		close(temp_fd);
		fds.in = open("heredoc_temp", O_RDONLY);
		Command *left_cmds = traverse_ast(node->left, fds, ope_stack, pipe_stack);
		Command *right_cmds = traverse_ast(node->right, fds, ope_stack, pipe_stack);
		if (left_cmds) {
			if (head == NULL) {
				head = tail = left_cmds;
			} else {
				tail->next = left_cmds;
				left_cmds->prev = tail;
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
				right_cmds->prev = tail;
			}
			while (tail->next) {
				tail = tail->next;
			}
		}
	}
	else if (node->type == NODE_AND || node->type == NODE_OR || node->type == NODE_SEMICOLON)
	{
		push_operator(ope_stack, node->type);
		Command *left_cmds = traverse_ast(node->left, fds, ope_stack, pipe_stack);
		Command *right_cmds = traverse_ast(node->right, fds, ope_stack, pipe_stack);
		if (left_cmds) {
			if (head == NULL) {
				head = tail = left_cmds;
			} else {
				tail->next = left_cmds;
				left_cmds->prev = tail;
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
				right_cmds->prev = tail;
			}
			while (tail->next) {
				tail = tail->next;
			}
		}
	}
	else if (node->type == NODE_PARENTHESIS)
	{
		NodeType parent_ope = peek_operator(*ope_stack);
		if (parent_ope == NODE_OUTPUT){
			fds.out = peek_pipe(*pipe_stack)->fdout;
			pop_pipe(pipe_stack);
		}
		push_operator(ope_stack, node->type);
		Command *left_cmds = traverse_ast(node->left, fds, ope_stack, pipe_stack);
		if (left_cmds) {
			if (head == NULL) {
				head = tail = left_cmds;
			} else {
				tail->next = left_cmds;
				left_cmds->prev = tail;
			}
			while (tail->next) {
				tail = tail->next;
			}
		}
	}
	// else {
	//     // Handle other node types as needed
	//     traverse_ast(node->left, fds.in, output_fd, ope_stack);
	//     traverse_ast(node->right, fds.in, output_fd, ope_stack);
	// }

	return head;
}
