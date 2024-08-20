#include "minishell.h"

void	exec_multiple_cmds(t_shell *data, t_cmd *cmd)
{
 	int	execution;

	execution = 0;
	if (!cmd)
		return ;
	//print_commands(data->cmd);
	if (cmd->parenthesis == 1 && cmd->parenthesis_status == P_OPEN)
        exec_parenthesis(data, cmd, &execution);
	else if (cmd->operator == NODE_OR || cmd->operator == NODE_AND)
		exec_bonus(data, cmd, &execution);
    else if (cmd->redirect == R_OUTFILE)
		exec_redir(data, cmd);
	else if (cmd->operator == NODE_PIPE || cmd->operator == NODE_END)
		exec_pipe(data, cmd);
}
