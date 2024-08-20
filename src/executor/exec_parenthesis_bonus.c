#include "minishell.h"

void	update_total_status(t_shell *data)
{
    if (data->status != 0)
        data->total_status = 1;
}

void	parenthesis_open(t_shell *data, t_cmd **cmd)
{
    while (*cmd != NULL && (*cmd)->parenthesis_status != P_CLOSE)
    {
        exec_one_cmd(data, *cmd);
        update_total_status(data);
        *cmd = (*cmd)->next;
    }
}

void	parenthesis_close(t_shell *data, t_cmd **cmd, int *execution)
{
    exec_one_cmd(data, *cmd);
    update_total_status(data);
    if (((*cmd)->operator == NODE_OR && data->total_status != 0) ||
        ((*cmd)->operator == NODE_AND && data->total_status == 0))
        *execution = 0;
    else
        *execution = 1;
    *cmd = (*cmd)->next;
}

void	exec_parenthesis(t_shell *data, t_cmd *cmd, int *execution)
{
    while (cmd != NULL)
    {
        if (cmd->parenthesis_status == P_OPEN)
        {
            data->total_status = 0;
			parenthesis_open(data, &cmd);
        }
		if (cmd != NULL && cmd->parenthesis_status == P_CLOSE)
			parenthesis_close(data, &cmd, execution);
        else if (cmd != NULL && cmd->parenthesis_status != P_OPEN)
        {
            if (cmd->operator == NODE_AND && data->status == 0)
                exec_node_and(data, cmd, execution);
            else if (cmd->operator == NODE_OR && data->status != 0)
                exec_node_or(data, cmd, execution);
            cmd = cmd->next;
        }
    }
}
