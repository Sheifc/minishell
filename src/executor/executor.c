#include "minishell.h"

void	executor(t_shell *data)
{
	t_cmd	*current;

	count_commands(data);
	current = data->cmd;
	if (!current)
		return ;
	set_tmp_fds(data);
	if (data->cmd_count == 1)
		exec_one_cmd(data, current);
	else if (data->cmd_count > 1)
	{
		if (current->operator == NODE_OR || current->operator == NODE_AND)
			exec_bonus(data, &current);
		else
			exec_multiple_cmds(data, current);
	}
	restart_fds(data);
}
