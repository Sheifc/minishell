#include "command.h"

void	postprocess_cmds(t_cmd *cmd)
{
	if (cmd == NULL)
		return ;
	if (ft_strcmp(cmd->name, "cat") == 0 && cmd->fdin == 0 && cmd->n_args == 1)
	{
		close(cmd->fdout);
		cmd->fdout = STDOUT_FILENO;
		if (cmd->operator == NODE_PIPE)
		{
			if (cmd->next)
			{
				close(cmd->next->fdin);
				cmd->next->fdin = STDIN_FILENO;
			}
		}
	}
	if (cmd->fdin != -1)
		cmd->redirect = R_INFILE;
	else if (cmd->fdout != -1)
		cmd->redirect = R_OUTFILE;
	while (cmd->next)
	{
		if (ft_strcmp(cmd->next->name, "save_outfile") != 0 && ft_strcmp(cmd->next->name,
				"read_infile") != 0 && ft_strcmp(cmd->next->name, "save_append") != 0
				&& ft_strcmp(cmd->next->name, "heredoc") != 0)
		break;
		cmd->operator = cmd->next->operator;
		if (cmd->fdout == -1)
			cmd->fdout = cmd->next->fdout;
		delete_command(&cmd->next);
	}
	cmd = cmd->next;
	postprocess_cmds(cmd);
}

t_cmd	*traverse_ast(ASTNode *node, Fds fds, OperatorStack **ope_stack,
	PipeStack **pipe_stack)
{
	if (node == NULL)
		return (NULL);
	if (node->type == NODE_COMMAND)
		return (handle_node_command(node, fds, ope_stack));
	else if (node->type == NODE_PIPE)
		return (handle_node_pipe(node, fds, ope_stack, pipe_stack));
	else if (node->type == NODE_OUTPUT || node->type == NODE_OUTPUT_APPEND)
		return (handle_node_output(node, fds, ope_stack, pipe_stack));
	else if (node->type == NODE_INPUT)
		return (handle_node_input(node, fds, ope_stack, pipe_stack));
	else if (node->type == NODE_HEREDOC)
		return (handle_node_heredoc(node, fds, ope_stack, pipe_stack));
	else if (node->type == NODE_AND || node->type == NODE_OR || 
		node->type == NODE_SEMICOLON)
		return (handle_node_and_or_semicolon(node, fds, ope_stack, pipe_stack));
	else if (node->type == NODE_PARENTHESIS)
		return (handle_node_parenthesis(node, fds, ope_stack, pipe_stack));
	else
		return (NULL);
}
