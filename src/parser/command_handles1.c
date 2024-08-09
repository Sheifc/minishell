#include "command.h"

void	ft_free_str(char *str)
{
	if (!str)
		free(str);
}

void	ft_read_stdin(int fd, char *eof)
{
	char	status;
	char	*line;
	char	*input;
	char	*temp_input;
	char	*replace_input;

	status = 0;
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
	replace_input = replace_env_variables(input, status);
	ft_free_str(input);
	write(fd, replace_input, ft_strlen(replace_input));
	ft_free_str(replace_input);
}

t_cmd	*handle_node_command(t_cmd_arg *arg, int *status)
{
	NodeType	parent_ope;
	t_cmd		*cmd;

	cmd = NULL;
	parent_ope = peek_operator(*arg->ope_stack);
	if (parent_ope == NODE_PARENTHESIS)
	{
		pop_operator(arg->ope_stack);
		parent_ope = peek_operator(*arg->ope_stack);
	}
	cmd = create_command_from_ast(arg, status, parent_ope);
	pop_operator(arg->ope_stack);
	return (cmd);
}

t_cmd	*handle_node_pipe(t_cmd_arg *arg, int *status)
{
	t_cmd	*head;
	t_cmd	*tail;
	t_cmd	*left_cmds;
	t_cmd	*right_cmds;
	// int		pipe_fds[2];
	ASTNode	*node;

	// pipe(pipe_fds);
	// printf(" \e[1;36mpipes: (W)%d => (R)%d\e[0m\n", pipe_fds[WRITE],
	// 	pipe_fds[READ]);
	push_operator(arg->ope_stack, arg->node->type);
	head = NULL;
	tail = NULL;
	node = arg->node;
	arg->node = node->left;
	left_cmds = traverse_ast(arg, status);
	arg->node = node->right;
	right_cmds = traverse_ast(arg, status);
	arg->node = node;
	append_commands(&head, &tail, left_cmds);
	append_commands(&head, &tail, right_cmds);
	return (head);
}

t_cmd	*handle_node_output(t_cmd_arg *arg, int *status)
{
	int		fd;
	t_cmd	*head;
	t_cmd	*tail;
	t_cmd	*left_cmds;
	t_cmd	*right_cmds;
	ASTNode	*node;

	fd = arg->fds.out;
	if (arg->node->right && arg->node->right->left)
	{
		if (ft_strncmp(arg->node->value, ">>", 2) == 0)
			fd = open(arg->node->right->left->value, O_WRONLY | O_CREAT | O_APPEND, 0644);
		else if (ft_strncmp(arg->node->value, ">", 1) == 0)
			fd = open(arg->node->right->left->value, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd == -1)
		{
			pop_operator(arg->ope_stack);
			ft_error_ope(E_FILE, arg->node->right->left->value, NULL, status);
			return (NULL);
		}
		push_pipe(arg->pipe_stack, arg->fds.in, fd);
	}
	push_operator(arg->ope_stack, arg->node->type);
	head = NULL;
	tail = NULL;
	node = arg->node;
	arg->node = node->left;
	left_cmds = traverse_ast(arg, status);
	arg->node = node->right;
	right_cmds = traverse_ast(arg, status);
	arg->node = node;
	append_commands(&head, &tail, left_cmds);
	if (left_cmds)
		tail->fdout = fd;
	append_commands(&head, &tail, right_cmds);
	return (head);
}

t_cmd	*handle_node_input(t_cmd_arg *arg, int *status)
{
	t_cmd	*head;
	t_cmd	*tail;
	t_cmd	*left_cmds;
	t_cmd	*right_cmds;
	int		fd;
	ASTNode	*node;

	fd = arg->fds.in;
	if (arg->node->right && arg->node->right->left)
	{
		fd = open(arg->node->right->left->value, O_RDONLY);
		if (fd == -1)
		{
			ft_error_ope(E_FILE, arg->node->right->left->value, NULL, status);
			return (NULL);
		}
		// printf(" \e[1;36mfile: (W)%d: infile: %s\e[0m\n", fd, node->right->left->value);
	}
	push_operator(arg->ope_stack, arg->node->type);
	head = NULL;
	tail = NULL;
	node = arg->node;
	arg->node = node->left;
	left_cmds = traverse_ast(arg, status);
	arg->node = node->right;
	right_cmds = traverse_ast(arg, status);
	arg->node = node;
	append_commands(&head, &tail, left_cmds);
	if (left_cmds)
		tail->fdin = fd;
	append_commands(&head, &tail, right_cmds);
	return (head);
}

t_cmd	*handle_node_heredoc(t_cmd_arg *arg, int *status)
{
	int		fd;
	t_cmd	*head;
	t_cmd	*tail;
	t_cmd	*left_cmds;
	t_cmd	*right_cmds;
	ASTNode	*node;

	push_operator(arg->ope_stack, NODE_INPUT);
	fd = open(".heredoc_temp", O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (arg->node->right && arg->node->right->left)
		ft_read_stdin(fd, arg->node->right->left->value);
	close(fd);
	fd = open(".heredoc_temp", O_RDONLY);
	head = NULL;
	tail = NULL;
	node = arg->node;
	arg->node = node->left;
	left_cmds = traverse_ast(arg, status);
	arg->node = node->right;
	right_cmds = traverse_ast(arg, status);
	arg->node = node;
	append_commands(&head, &tail, left_cmds);
	if (left_cmds)
		tail->fdin = fd;
	append_commands(&head, &tail, right_cmds);
	return (head);
}
