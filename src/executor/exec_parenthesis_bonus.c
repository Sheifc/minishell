#include "minishell.h"

void	update_total_status(t_shell *data)
{
    if (data->status != 0)
        data->total_status = 1;
}

void	exec_or_parenthesis(t_shell *data, t_cmd *cmd, int *execution, int *flag)
{
	(void)data;
	(void)cmd;
	(void)execution;
	(void)flag;
}

void	exec_and_parenthesis(t_shell *data, t_cmd *cmd, int *execution, int *flag)
{
	(void)data;
	(void)cmd;
	(void)execution;
	(void)flag;
}

void	exec_parenthesis(t_shell *data, t_cmd *cmd, int *execution, int *flag)
{
	(void)data;
	(void)cmd;
	(void)execution;
	(void)flag;
}
