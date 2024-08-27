/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_handles_b.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sheferna <sheferna@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 18:46:12 by sheferna          #+#    #+#             */
/*   Updated: 2024/08/27 18:46:13 by sheferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.h"

t_cmd	*create_command(t_cmd_arg *arg, t_shell *data)
{
	t_cmd		*cmd;
	char		*value;

	cmd = (t_cmd *)malloc(sizeof(t_cmd));
	if (!cmd)
	{
		ft_error(E_MEMORY, NULL, &data->status);
		return (NULL);
	}
	value = replace_env_variables(arg->node->value, data);
	cmd->name = parse_string(value, data);
	cmd->arg = NULL;
	cmd->n_args = 0;
	cmd->fdin = arg->fds.in;
	cmd->fdout = arg->fds.out;
	cmd->parenthesis = data->parenthesis;
	cmd->parenthesis_status = P_NONE;
	handle_parenthesis_status(cmd, arg);
	cmd->next = NULL;
	cmd->redirect = R_NONE;
	add_argument(cmd, value, data);
	free(value);
	return (cmd);
}

t_cmd	*create_command_from_ast(t_cmd_arg *arg, t_shell *data)
{
	t_cmd		*cmd;
	t_ast_node	*arg_node;
	char		*preproc_input;

	cmd = create_command(arg, data);
	arg_node = arg->node->left;
	while (arg_node)
	{
		if (arg_node->type == NODE_ARGUMENT)
		{
			if (arg->node->type != NODE_HEREDOC)
				preproc_input = replace_env_variables(arg_node->value, data);
			else
				preproc_input = ft_strdup(arg_node->value);
			add_argument(cmd, preproc_input, data);
			ft_free_str(&preproc_input);
		}
		arg_node = arg_node->left;
	}
	return (cmd);
}

void	append_commands(t_cmd **head, t_cmd **tail, t_cmd *new_cmds)
{
	if (new_cmds)
	{
		if (*head == NULL)
		{
			*head = new_cmds;
			*tail = new_cmds;
		}
		else
		{
			(*tail)->next = new_cmds;
		}
		while ((*tail)->next)
		{
			*tail = (*tail)->next;
		}
	}
}

t_cmd	*handle_node_and_or_semicolon(t_cmd_arg *arg, t_shell *data)
{
	t_cmd		*head;
	t_cmd		*tail;
	t_cmd		*left_cmds;
	t_cmd		*right_cmds;
	t_ast_node	*node;

	node = arg->node;
	push_operator(arg->ope_stack, arg->node->type);
	head = NULL;
	tail = NULL;
	arg->node = node->left;
	left_cmds = traverse_ast(arg, data);
	arg->node = node->right;
	right_cmds = traverse_ast(arg, data);
	arg->node = node;
	append_commands(&head, &tail, left_cmds);
	append_commands(&head, &tail, right_cmds);
	return (head);
}

t_cmd	*handle_node_parenthesis(t_cmd_arg *arg, t_shell *data)
{
	t_node_type	parent_ope;
	t_cmd		*head;
	t_cmd		*tail;
	t_cmd		*left_cmds;
	t_ast_node	*node;

	parent_ope = peek_operator(*arg->ope_stack);
	if (parent_ope == NODE_OUTPUT || parent_ope == NODE_OUTPUT_APPEND)
	{
		arg->fds.out = peek_pipe(*arg->pipe_stack)->fdout;
		pop_pipe(arg->pipe_stack);
	}
	push_operator(arg->ope_stack, arg->node->type);
	head = NULL;
	tail = NULL;
	node = arg->node;
	arg->node = node->left;
	arg->open_parenthesis = true;
	left_cmds = traverse_ast(arg, data);
	arg->node = node;
	append_commands(&head, &tail, left_cmds);
	return (head);
}
