#include "command.h"

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
	// int		pipe_fds[2];
	// pipe(pipe_fds);
	// printf(" \e[1;36mpipes: (W)%d => (R)%d\e[0m\n", pipe_fds[WRITE],
	// 	pipe_fds[READ]);
	push_operator(arg->ope_stack, arg->node->type);
	return (process_node_commands(arg, status, 0, R_NONE));
}

t_cmd	*handle_node_output(t_cmd_arg *arg, int *status)
{
	int	fd;

	fd = arg->fds.out;
	if (arg->node->right && arg->node->right->left)
	{
		if (ft_strncmp(arg->node->value, ">>", 2) == 0)
			fd = open(arg->node->right->left->value,
					O_WRONLY | O_CREAT | O_APPEND, 0644);
		else if (ft_strncmp(arg->node->value, ">", 1) == 0)
			fd = open(arg->node->right->left->value,
					O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd == -1)
		{
			pop_operator(arg->ope_stack);
			ft_error_ope(E_FILE, arg->node->right->left->value, NULL, status);
			return (NULL);
		}
		push_pipe(arg->pipe_stack, arg->fds.in, fd);
	}
	push_operator(arg->ope_stack, arg->node->type);
	return (process_node_commands(arg, status, fd, R_OUTFILE));
}

t_cmd	*handle_node_input(t_cmd_arg *arg, int *status)
{
	int	fd;

	fd = arg->fds.in;
	if (arg->node->right && arg->node->right->left)
	{
		fd = open(arg->node->right->left->value, O_RDONLY);
		if (fd == -1)
		{
			ft_error_ope(E_FILE, arg->node->right->left->value, NULL, status);
			return (NULL);
		}
		// printf(" \e[1;36mfile: (W)%d: infile: %s\e[0m\n", fd,
		//	node->right->left->value);
	}
	push_operator(arg->ope_stack, arg->node->type);
	return (process_node_commands(arg, status, fd, R_INFILE));
}

t_cmd	*handle_node_heredoc(t_cmd_arg *arg, int *status)
{
	int	fd;

	fd = open(".heredoc_temp", O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (arg->node->right && arg->node->right->left)
		ft_read_stdin(fd, arg->node->right->left->value, status);
	close(fd);
	fd = open(".heredoc_temp", O_RDONLY);
	push_operator(arg->ope_stack, NODE_HEREDOC);
	return (process_node_commands(arg, status, fd, R_INFILE));
}
