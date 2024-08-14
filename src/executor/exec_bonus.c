#include "minishell.h"

void	exec_node_or(t_shell *data, t_cmd *cmd, int *execution)
{
	if (*execution == 0)
	{
		exec_one_cmd(data, cmd);
		*execution = 1;
	}
	else
	{
		if (cmd->next && cmd->next->parenthesis == 1)
		{
			if (data->status != 0)
				exec_parenthesis(data, cmd->next, execution, &data->status);
		}
		else if (cmd->next && cmd->next->parenthesis == 0)
		{
			if (data->status != 0)
				exec_bonus(data, cmd->next, execution);
		}
	}
}

void	exec_node_and(t_shell *data, t_cmd *cmd, int *execution)
{
	if (*execution == 0)
	{
		exec_one_cmd(data, cmd);
		*execution = 1;
	}
	else
	{
		if (cmd->next && cmd->next->parenthesis == 1)
		{
			if (data->status == 0)
				exec_parenthesis(data, cmd->next, execution, &data->status);
		}
		else if (cmd->next && cmd->next->parenthesis == 0)
		{
			if (data->status && data->status == 0)
				exec_bonus(data, cmd->next, execution);
		}
	}
}

void	exec_bonus(t_shell *data, t_cmd *cmd, int *execution)
{
	if (cmd != NULL && (cmd->operator == NODE_AND || cmd->operator == NODE_OR))
	{
		if (cmd->operator == NODE_AND)
			exec_node_and(data, cmd, execution);
		else if (cmd->operator == NODE_OR)
			exec_node_or(data, cmd, execution);
	}
	else if(cmd != NULL && (cmd->operator == NODE_PIPE || cmd->operator == NODE_END))
		exec_multiple_cmds(data, cmd);
}

void	exec_parenthesis(t_shell *data, t_cmd *cmd, int *execution, int *total_status)
{
	if (cmd->parenthesis == 1 && *execution == 0)
	{
		exec_one_cmd(data, cmd);
		*total_status = data->status;
		*execution = 1;
		if (cmd->next)
			exec_parenthesis(data, cmd->next, execution, total_status);
	}
	else if (cmd->parenthesis == 1 && *execution == 1)
	{
		if (cmd->operator == NODE_AND)
		{
			if (data->status == 0)
			{
				exec_one_cmd(data, cmd);
				if (data->status != 0)
					*total_status = 1;
			}
		}
		else if (cmd->operator == NODE_OR)
		{
			if (data->status != 0)
			{
				exec_one_cmd(data, cmd);
				if (data->status == 0)
					*total_status = 0;
			}
		}
		if (cmd->next)
		{
			if (cmd->next->parenthesis == 1)
				exec_parenthesis(data, cmd->next, execution, total_status);
			else
			{
				if (cmd->operator == NODE_AND)
				{
					if (total_status == 0)
						exec_bonus(data, cmd->next, execution);
				}
				else if (cmd->operator == NODE_OR)
				{
					if (total_status != 0)
						exec_bonus(data, cmd->next, execution);
				}
			}
		}
	}
}
