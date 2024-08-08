#include "minishell.h"

void	exec_node_or(t_shell *data, t_cmd **cmd)
{
	//dprintf(2, "\n****entra en node or\n");
	//dprintf(2, "\ncmd->arg[0]: %s\n", (*cmd)->arg[0]);
	exec_one_cmd(data, *cmd);
	//dprintf(2, "status: %d\n", data->status);
	if ((*cmd)->next && data->status != 0 && (*cmd)->operator == NODE_OR)
	{
		*cmd = (*cmd)->next;
		exec_node_or(data, cmd);
	}
}

void	exec_node_and(t_shell *data, t_cmd **cmd)
{
	//dprintf(2, "\n*****entra en node and\n");
	//dprintf(2, "\ncmd->arg[0]: %s\n", (*cmd)->arg[0]);
	exec_one_cmd(data, *cmd);
	//dprintf(2, "status tras primera ejecucion: %d\n", data->status);
	if ((*cmd)->next && data->status == 0 && (*cmd)->operator == NODE_AND)
	{
		*cmd = (*cmd)->next;
		exec_node_and(data, cmd);
		//dprintf(2, "status tras segunda ejecucion: %d\n", data->status);
	}
}

void	exec_bonus(t_shell *data, t_cmd **cmd)
{

	if (cmd != NULL && ((*cmd)->operator == NODE_AND \
	|| (*cmd)->operator == NODE_OR))
	{
		if ((*cmd)->operator == NODE_AND)
		{
			exec_node_and(data, cmd);
		}
		else if ((*cmd)->operator == NODE_OR)
		{
			exec_node_or(data, cmd);
		}
		else
			exec_bonus(data, &(*cmd)->next);
	}
}
