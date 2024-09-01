/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_handles_a.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svilla-d <svilla-d@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 18:46:07 by sheferna          #+#    #+#             */
/*   Updated: 2024/09/01 10:29:02 by svilla-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.h"
#include "minishell.h"

void	handle_parenthesis_status(t_cmd *cmd, t_cmd_arg *arg)
{
	t_node_type	ope;

	ope = peek_operator(*arg->ope_stack);
	if (arg->open_parenthesis && ope != NODE_PARENTHESIS)
		cmd->parenthesis_status = P_OPEN;
	if (ope == NODE_PARENTHESIS)
	{
		if (!arg->open_parenthesis)
			cmd->parenthesis_status = P_CLOSE;
		pop_operator(arg->ope_stack);
		ope = peek_operator(*arg->ope_stack);
	}
	cmd->operator = ope;
}

t_cmd	*handle_node_command(t_cmd_arg *arg, t_shell *data)
{
	t_cmd		*cmd;

	cmd = NULL;
	data->parenthesis = count_operator(*arg->ope_stack, NODE_PARENTHESIS);
	cmd = create_command_from_ast(arg, data);
	if (arg->open_parenthesis == true)
		arg->open_parenthesis = false;
	pop_operator(arg->ope_stack);
	return (cmd);
}

t_cmd	*handle_node_output(t_cmd_arg *arg, t_shell *data)
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
			ft_error_ope(E_FILE, arg->node->right->left->value, NULL,
				&data->status);
			return (NULL);
		}
		push_pipe(arg->pipe_stack, arg->fds.in, fd);
	}
	push_operator(arg->ope_stack, arg->node->type);
	return (process_node_commands(arg, data, fd, R_OUTFILE));
}

t_cmd	*handle_node_input(t_cmd_arg *arg, t_shell *data)
{
	int	fd;

	fd = arg->fds.in;
	if (arg->node->right && arg->node->right->left)
	{
		fd = open(arg->node->right->left->value, O_RDONLY);
		if (fd == -1)
		{
			ft_error_ope(E_FILE, arg->node->right->left->value, NULL,
				&data->status);
			return (NULL);
		}
	}
	push_operator(arg->ope_stack, arg->node->type);
	return (process_node_commands(arg, data, fd, R_INFILE));
}

t_cmd	*handle_node_heredoc(t_cmd_arg *arg, t_shell *data)
{
	pid_t	pid;
	int		fd;
	t_cmd	*c;

	c = process_node_commands(arg, data, -1, R_INFILE);
	pid = fork();
	if (pid == -1)
		return (ft_error(E_AUTO, "heredoc fork failed", &data->status));
	if (pid == 0)
	{
		signal(SIGINT, heredoc_handler);
		fd = open(".heredoc_temp", O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (arg->node->right && arg->node->right->left)
			ft_read_stdin(fd, arg->node->right->left->value, data);
		close(fd);
		free_commands(&c);
		free_all(data);
		exit(EXIT_SUCCESS);
	}
	signal(SIGINT, SIG_IGN);
	wait_pid(pid, data);
	fd = open(".heredoc_temp", O_RDONLY);
	push_operator(arg->ope_stack, NODE_HEREDOC);
	signal(SIGINT, sigint_handler);
	return (unlink(".heredoc_temp"), c->fdin = fd, c);
}
