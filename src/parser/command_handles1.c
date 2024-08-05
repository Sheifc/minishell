#include "command.h"

void	ft_free_str(char *str)
{
	if (!str)
		free(str);
}

void	ft_read_stdin(int fd, char *eof)
{
	char	*line;
	char	*input;
	char	*temp_input;
	char	*replace_input;

	input = ft_strdup("");
	while (1)
	{
		line = get_next_line(STDIN_FILENO);
		if (line && ft_strcmp(line, eof) == OK)
			break ;
		if (line)
		{
			temp_input = ft_strdup(input);
			ft_free_str(input);
			input = ft_strjoin(temp_input, line);
			ft_free_str(temp_input);
		}
		else if (!line)
			input = ft_strdup(line);
		ft_free_str(line);
	}
	replace_input = replace_env_variables(input);
	ft_free_str(input);
	write(fd, replace_input, ft_strlen(replace_input));
	ft_free_str(replace_input);
}

t_cmd	*handle_node_command(ASTNode *node, Fds fds, OperatorStack **ope_stack)
{
	NodeType	parent_ope;
	t_cmd		*cmd;

	cmd = NULL;
	parent_ope = peek_operator(*ope_stack);
	if (parent_ope == NODE_PARENTHESIS)
	{
		pop_operator(ope_stack);
		parent_ope = peek_operator(*ope_stack);
	}
	if (ft_strcmp(node->value, "save_outfile") != 0 && ft_strcmp(node->value,
			"read_infile") != 0 && ft_strcmp(node->value, "save_append") != 0
			&& ft_strcmp(node->value, "heredoc") != 0)
		cmd = create_command_from_ast(node, fds, parent_ope);
	pop_operator(ope_stack);
	return (cmd);
}

t_cmd	*handle_node_pipe(ASTNode *node, Fds fds, OperatorStack **ope_stack,
		PipeStack **pipe_stack)
{
	t_cmd	*head;
	t_cmd	*tail;
	t_cmd	*left_cmds;
	t_cmd	*right_cmds;
	int		pipe_fds[2];

	pipe(pipe_fds);
	// printf(" \e[1;36mpipes: (W)%d => (R)%d\e[0m\n", pipe_fds[WRITE],
	// 	pipe_fds[READ]);
	push_operator(ope_stack, node->type);
	head = NULL;
	tail = NULL;
	left_cmds = traverse_ast(node->left, (Fds){fds.in, fds.out}, ope_stack,
			pipe_stack);
	right_cmds = traverse_ast(node->right, (Fds){fds.in, fds.out}, ope_stack,
			pipe_stack);
	append_commands(&head, &tail, left_cmds);
	append_commands(&head, &tail, right_cmds);
	return (head);
}

t_cmd	*handle_node_output(ASTNode *node, Fds fds, OperatorStack **ope_stack,
		PipeStack **pipe_stack)
{
	int		fd;
	t_cmd	*head;
	t_cmd	*tail;
	t_cmd	*left_cmds;
	t_cmd	*right_cmds;

	push_operator(ope_stack, node->type);
	fd = fds.out;
	if (ft_strncmp(node->value, ">>", 2) == 0)
		fd = open(node->right->left->value, O_WRONLY | O_CREAT | O_APPEND,
				0644);
	else if (ft_strncmp(node->value, ">", 1) == 0)
		fd = open(node->right->left->value, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	push_pipe(pipe_stack, fds.in, fd);
	//printf(" \e[1;36mfile: (W)%d\e[0m\n", fd);
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

t_cmd	*handle_node_input(ASTNode *node, Fds fds, OperatorStack **ope_stack,
		PipeStack **pipe_stack)
{
	t_cmd	*head;
	t_cmd	*tail;
	t_cmd	*left_cmds;
	t_cmd	*right_cmds;

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

t_cmd	*handle_node_heredoc(ASTNode *node, Fds fds, OperatorStack **ope_stack,
		PipeStack **pipe_stack)
{
	int		fd;
	t_cmd	*head;
	t_cmd	*tail;
	t_cmd	*left_cmds;
	t_cmd	*right_cmds;

	push_operator(ope_stack, NODE_INPUT);
	fd = open(".heredoc_temp", O_WRONLY | O_CREAT | O_APPEND, 0644);
	ft_read_stdin(fd, node->right->left->value);
	close(fd);
	fds.in = open(".heredoc_temp", O_RDONLY);
	head = NULL;
	tail = NULL;
	left_cmds = traverse_ast(node->left, fds, ope_stack, pipe_stack);
	right_cmds = traverse_ast(node->right, fds, ope_stack, pipe_stack);
	append_commands(&head, &tail, left_cmds);
	append_commands(&head, &tail, right_cmds);
	return (head);
}
