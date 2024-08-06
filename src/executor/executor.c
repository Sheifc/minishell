#include "minishell.h"

void	get_status(t_shell *data)
{
	if (WIFEXITED(data->status))
		data->status = WEXITSTATUS(data->status);
	else if (WIFSIGNALED(data->status))
		data->status = WTERMSIG(data->status);
}

void	exec_one_cmd(t_shell *data, t_cmd *cmd)
{
	set_fdin(data, cmd);
	set_fdout(data, cmd);
	if (!execute_builtin(data, cmd, cmd->arg[0]))
	{
		data->pid = fork();
		if (data->pid < 0)
			perror("Error: fork failed");
		else if (data->pid == 0)
		{
			get_path(data, cmd);
			if (!data->path)
			{
				perror("Error: command not found");
				exit(127);
			}
			if (execve(data->path, cmd->arg, data->envp) < 0)
			{
				perror("Error: execve failed");
				exit(1);
			}
		}
		waitpid(data->pid, &(data->status), 0);
		get_status(data);
	}
	close(cmd->fdin);
	close(cmd->fdout);
}

void	executor(t_shell *data)
{
	t_cmd	*current;

	count_commands(data);
	current = data->cmd;
	if (!current)
		return ;
	//print_commands(current);
	set_tmp_fds(data);
	if (data->cmd_count == 1)
		exec_one_cmd(data, current);
	else if (data->cmd_count > 1)
		exec_multiple_cmds(data, current);
	restart_fds(data);
}
