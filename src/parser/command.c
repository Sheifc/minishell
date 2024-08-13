#include "command.h"

void	clean_commands(t_cmd *cmd)
{
	while (cmd->next)
	{
		if (ft_strcmp(cmd->next->name, "save_outfile") != 0
			&& ft_strcmp(cmd->next->name, "read_infile") != 0
			&& ft_strcmp(cmd->next->name, "save_append") != 0
			&& ft_strcmp(cmd->next->name, "heredoc") != 0)
			break ;
		cmd->operator = cmd->next->operator;
		if (cmd->next->fdout != -1)
			cmd->fdout = cmd->next->fdout;
		delete_command(&cmd->next);
	}
}

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
	clean_commands(cmd);
	cmd = cmd->next;
	postprocess_cmds(cmd);
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
		return (handle_node_pipe(arg, data));
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
