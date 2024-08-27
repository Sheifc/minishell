/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sheferna <sheferna@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 18:46:27 by sheferna          #+#    #+#             */
/*   Updated: 2024/08/27 18:46:28 by sheferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.h"

void	clean_commands(t_cmd **cmd, t_cmd **head)
{
	while ((*cmd)->next)
	{
		if (ft_strcmp((*cmd)->next->name, "save_outfile") != 0
			&& ft_strcmp((*cmd)->next->name, "read_infile") != 0
			&& ft_strcmp((*cmd)->next->name, "save_append") != 0
			&& ft_strcmp((*cmd)->next->name, "heredoc") != 0)
			break ;
		(*cmd)->operator = (*cmd)->next->operator;
		if ((*cmd)->next->fdout != -1)
		{
			(*cmd)->fdout = (*cmd)->next->fdout;
			(*cmd)->redirect = R_OUTFILE;
		}
		delete_command(&(*cmd)->next, head);
	}
	if (*cmd && (ft_strcmp((*cmd)->name, "save_outfile") == 0
			|| ft_strcmp((*cmd)->name, "read_infile") == 0
			|| ft_strcmp((*cmd)->name, "save_append") == 0
			|| ft_strcmp((*cmd)->name, "heredoc") == 0))
		delete_command(cmd, head);
}

void	postprocess_cmds(t_shell *data)
{
	t_cmd	*current_cmd;

	current_cmd = data->cmd;
	while (current_cmd != NULL)
	{
		if (current_cmd->fdin != -1)
			current_cmd->redirect = R_INFILE;
		else if (current_cmd->fdout != -1)
			current_cmd->redirect = R_OUTFILE;
		clean_commands(&current_cmd, &data->cmd);
		if (current_cmd)
			current_cmd = current_cmd->next;
	}
}

t_cmd	*traverse_ast(t_cmd_arg *arg, t_shell *data)
{
	t_ast_node	*node;

	node = arg->node;
	if (arg == NULL || arg->node == NULL)
		return (NULL);
	if (node->type == NODE_COMMAND)
		return (handle_node_command(arg, data));
	else if (node->type == NODE_PIPE)
	{
		push_operator(arg->ope_stack, arg->node->type);
		return (process_node_commands(arg, data, 0, R_NONE));
	}
	else if (node->type == NODE_OUTPUT || node->type == NODE_OUTPUT_APPEND)
		return (handle_node_output(arg, data));
	else if (node->type == NODE_INPUT)
		return (handle_node_input(arg, data));
	else if (node->type == NODE_HEREDOC)
		return (handle_node_heredoc(arg, data));
	else if (node->type == NODE_AND || node->type == NODE_OR
		|| node->type == NODE_SEMICOLON)
		return (handle_node_and_or_semicolon(arg, data));
	else if (node->type == NODE_PARENTHESIS)
		return (handle_node_parenthesis(arg, data));
	else
		return (NULL);
}
