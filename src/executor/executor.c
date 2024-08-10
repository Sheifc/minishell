#include "minishell.h"

void	executor(t_shell *data)
{
	t_cmd	*current;

	count_commands(data);
	current = data->cmd;
	if (!current)
		return ;
	print_commands(current);
	set_tmp_fds(data);
	if (data->cmd_count == 1)
		exec_one_cmd(data, current);
	else if (data->cmd_count > 1)
	{
		if (current->operator == NODE_OR || current->operator == NODE_AND)
			exec_bonus(data, &current);
		else if (current->redirect == R_INFILE || current->redirect == R_OUTFILE)
			exec_redir(data, current);
		else if (current->operator == NODE_PIPE || current->operator == NODE_END)
			exec_pipe(data, current);
	}
	restart_fds(data);
}
