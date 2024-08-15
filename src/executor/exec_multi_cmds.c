#include "minishell.h"

void	exec_multiple_cmds(t_shell *data, t_cmd *cmd)
{
 	int	execution;
	int	flag;

	execution = 0;
	flag = 1;
	if (!cmd)
		return ;
	//print_commands(data->cmd);
	if (cmd->parenthesis == 1 && flag == 1)
        exec_parenthesis(data, cmd, &execution, &flag);
	else if (cmd->operator == NODE_OR || cmd->operator == NODE_AND)
		exec_bonus(data, cmd, &execution);
    else if (cmd->redirect == R_OUTFILE)
		exec_redir(data, cmd);
	else if (cmd->operator == NODE_PIPE || cmd->operator == NODE_END)
		exec_pipe(data, cmd);
}
