#include "minishell.h"

/* void	exec_node_or(t_shell *data, t_cmd **cmd, int *execution)
{
	//dprintf(2, "\n****entra en node or\n");
	//dprintf(2, "\ncmd->arg[0]: %s\n", (*cmd)->arg[0]);
	if (*execution == 0)
	{
		exec_one_cmd(data, *cmd);
		*execution = 1;
	}
	//dprintf(2, "status: %d\n", data->status);
	if ((*cmd)->next && data->status != 0 && (*cmd)->next->operator == NODE_OR)
	{
		*cmd = (*cmd)->next;
		exec_node_or(data, cmd, execution);
		//dprintf(2, "status tras segunda ejecucion: %d\n", data->status);
	}
}

void	exec_node_and(t_shell *data, t_cmd **cmd, int *execution)
{
	//dprintf(2, "\n*****entra en node and\n");
	//dprintf(2, "\ncmd->arg[0]: %s\n", (*cmd)->arg[0]);
	if (*execution == 0)
	{
		exec_one_cmd(data, *cmd);
		*execution = 1;
	}
	//dprintf(2, "status tras primera ejecucion: %d\n", data->status);
	if ((*cmd)->next && data->status == 0 && (*cmd)->next->operator == NODE_AND)
	{
		*cmd = (*cmd)->next;
		exec_node_and(data, cmd, execution);
		//dprintf(2, "status tras segunda ejecucion: %d\n", data->status);
	}
}

void	exec_bonus(t_shell *data, t_cmd **cmd)
{
	int execution = 0;

	if (cmd != NULL && ((*cmd)->operator == NODE_AND \
	|| (*cmd)->operator == NODE_OR))
	{
		if ((*cmd)->operator == NODE_AND)
		{
			exec_node_and(data, cmd, &execution);
		}
		if ((*cmd)->operator == NODE_OR)
		{
			exec_node_or(data, cmd, &execution);
		}
		exec_bonus(data, &(*cmd)->next);
	}
} */

void	exec_node_or(t_shell *data, t_cmd *cmd, int *execution)
{
	if (*execution == 0)
	{
		exec_one_cmd(data, cmd);
		*execution = 1;
	}

	if (cmd->next && data->status != 0 && cmd->next->operator == NODE_OR)
	{
		exec_node_or(data, cmd->next, execution);
	}
}

void	exec_node_and(t_shell *data, t_cmd *cmd, int *execution)
{
	if (*execution == 0)
	{
		exec_one_cmd(data, cmd);
		*execution = 1;
	}

	if (cmd->next && data->status == 0 && cmd->next->operator == NODE_AND)
	{
		exec_node_and(data, cmd->next, execution);
	}
}

void	exec_bonus(t_shell *data, t_cmd *cmd)
{
	int execution = 0;

	if (cmd != NULL && (cmd->operator == NODE_AND || cmd->operator == NODE_OR))
	{
		if (cmd->operator == NODE_AND)
		{
			exec_node_and(data, cmd, &execution);
		}
		else if (cmd->operator == NODE_OR)
		{
			exec_node_or(data, cmd, &execution);
		}
		exec_bonus(data, cmd->next);
	}
	else if(cmd != NULL && cmd->operator == NODE_PIPE)
	{
		exec_multiple_cmds(data, cmd);
	}
}

