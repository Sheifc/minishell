#include "command.h"

Command	*handle_node_command(ASTNode *node, Fds fds, OperatorStack **ope_stack)
{
	NodeType	parent_ope;
	Command		*cmd;

	parent_ope = peek_operator(*ope_stack);
	if (parent_ope == NODE_PARENTHESIS)
	{
		pop_operator(ope_stack);
		parent_ope = peek_operator(*ope_stack);
	}
	cmd = create_command_from_ast(node, fds, parent_ope);
	pop_operator(ope_stack);
	return (cmd);
}

Command	*handle_node_pipe(ASTNode *node, Fds fds, OperatorStack **ope_stack,
	PipeStack **pipe_stack)
{
	Command	*head;
	Command	*tail;
	Command	*left_cmds;
	Command	*right_cmds;
	int		pipe_fds[2];

	pipe(pipe_fds);
	printf(" \e[1;36mpipes: (W)%d => (R)%d\e[0m\n", pipe_fds[WRITE],
		pipe_fds[READ]);
	push_operator(ope_stack, node->type);
	head = NULL;
	tail = NULL;
	left_cmds = traverse_ast(node->left, (Fds){fds.in, pipe_fds[WRITE]},
			ope_stack, pipe_stack);
	right_cmds = traverse_ast(node->right, (Fds){pipe_fds[READ], fds.out},
			ope_stack, pipe_stack);
	append_commands(&head, &tail, left_cmds);
	append_commands(&head, &tail, right_cmds);
	return (head);
}

Command	*handle_node_output(ASTNode *node, Fds fds, OperatorStack **ope_stack,
	PipeStack **pipe_stack)
{
	int		fd;
	Command	*head;
	Command	*tail;
	Command	*left_cmds;
	Command	*right_cmds;

	push_operator(ope_stack, node->type);
	fd = fds.out;
	if (ft_strncmp(node->value, ">>", 2) == 0)
		fd = open(node->right->left->value, O_WRONLY | O_CREAT | O_APPEND,
				0644);
	else if (ft_strncmp(node->value, ">", 1) == 0)
		fd = open(node->right->left->value, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	push_pipe(pipe_stack, fds.in, fd);
	printf(" \e[1;36mfile: (W)%d\e[0m\n", fd);
	head = NULL;
	tail = NULL;
	left_cmds = traverse_ast(node->left, fds, ope_stack, pipe_stack);
	right_cmds = traverse_ast(node->right, fds, ope_stack, pipe_stack);
	append_commands(&head, &tail, left_cmds);
	if (left_cmds)
		tail->fdout = fd;
	append_commands(&head, &tail, right_cmds);
	return (head);
}

Command	*handle_node_input(ASTNode *node, Fds fds, OperatorStack **ope_stack,
	PipeStack **pipe_stack)
{
	Command	*head;
	Command	*tail;
	Command	*left_cmds;
	Command	*right_cmds;

	push_operator(ope_stack, node->type);
	fds.in = open(node->right->left->value, O_RDONLY);
	head = NULL;
	tail = NULL;
	left_cmds = traverse_ast(node->left, fds, ope_stack, pipe_stack);
	right_cmds = traverse_ast(node->right, fds, ope_stack, pipe_stack);
	append_commands(&head, &tail, left_cmds);
	append_commands(&head, &tail, right_cmds);
	return (head);
}

Command	*handle_node_heredoc(ASTNode *node, Fds fds, OperatorStack **ope_stack,
	PipeStack **pipe_stack)
{
	int		fd;
	Command	*head;
	Command	*tail;
	Command	*left_cmds;
	Command	*right_cmds;

	push_operator(ope_stack, node->type);
	fd = open("heredoc_temp", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	write(fd, node->right->left->value, strlen(node->right->left->value)); 
	close(fd);
	fds.in = open("heredoc_temp", O_RDONLY);
	head = NULL;
	tail = NULL;
	left_cmds = traverse_ast(node->left, fds, ope_stack, pipe_stack);
	right_cmds = traverse_ast(node->right, fds, ope_stack, pipe_stack);
	append_commands(&head, &tail, left_cmds);
	append_commands(&head, &tail, right_cmds);
	return (head);
}
