#include "minishell.h"

void	update_total_status(t_shell *data)
{
    if (data->status != 0)
        data->total_status = 1;
}

/* void	exec_or_parenthesis(t_shell *data, t_cmd *cmd, int *execution, int *flag)
{
	//(void)data;
	//(void)cmd;
	//(void)execution;
	(void)flag;
	if (*execution == 0)
	{
		exec_one_cmd(data, cmd);
		update_total_status(data);
		*execution = 1;
	}
	if (cmd->next && cmd->next->parenthesis == 1 && data->status == 0)
	{
		*execution = 0;
		exec_parenthesis(data, cmd->next, execution, flag);
	}
}

void	exec_and_parenthesis(t_shell *data, t_cmd *cmd, int *execution, int *flag)
{
	//(void)data;
	//(void)cmd;
	//(void)execution;
	(void)flag;
	if (*execution == 0)
	{
		exec_one_cmd(data, cmd);
		update_total_status(data);
		*execution = 1;
	}
	if (cmd->next && cmd->next->parenthesis == 1 && data->status == 0)
	{
		*execution = 0;
		exec_parenthesis(data, cmd->next, execution, flag);
	}
	else if (cmd->next && cmd->next->parenthesis == 0)
	{
		*execution = 0;

	}
}*/

void	exec_parenthesis(t_shell *data, t_cmd *cmd, int *execution, int *flag)
{
	(void)data;
	(void)cmd;
	(void)execution;
	(void)flag;
/* 	if (cmd != NULL && cmd->parenthesis == 1)
	{
		if (cmd->operator == NODE_AND)
			exec_and_parenthesis(data, cmd, execution, flag);
		else if (cmd->operator == NODE_OR)
			exec_or_parenthesis(data, cmd, execution, flag);
		else if (cmd->next)
			exec_parenthesis(data, cmd->next, execution, flag);
	} */
}

/* void exec_parenthesis(t_shell *data, t_cmd *cmd, int *execution, int *flag)
{
    if (cmd->parenthesis_status == P_OPEN)
    {
        int local_execution = 0;
        t_cmd *current = cmd;

        while (current && current->parenthesis_status != P_CLOSE)
        {
            if (current->operator == NODE_AND)
                exec_and_parenthesis(data, current, &local_execution, flag);
            else if (current->operator == NODE_OR)
                exec_or_parenthesis(data, current, &local_execution, flag);
            else
                exec_one_cmd(data, current);

            current = current->next;
        }
        *execution = local_execution;
        update_total_status(data);
    }
}

void exec_or_parenthesis(t_shell *data, t_cmd *cmd, int *execution, int *flag)
{
    if (*execution == 0)
    {
        exec_one_cmd(data, cmd);
        update_total_status(data);
        *execution = 1;
    }
    
    if (cmd->next && cmd->next->parenthesis_status == P_OPEN && data->status == 0)
    {
        exec_parenthesis(data, cmd->next, execution, flag);
    }
}

void exec_and_parenthesis(t_shell *data, t_cmd *cmd, int *execution, int *flag)
{
    if (*execution == 0)
    {
        exec_one_cmd(data, cmd);
        update_total_status(data);
        *execution = 1;
    }
    
    if (cmd->next && cmd->next->parenthesis_status == P_OPEN && data->status == 0)
    {
        exec_parenthesis(data, cmd->next, execution, flag);
    }
    else if (cmd->next && cmd->next->parenthesis_status == P_NONE)
    {
        *execution = 0;
    }
} */