#include "minishell.h"

void	get_status(t_shell *data)
{
	if (WIFEXITED(data->status))
		data->status = WEXITSTATUS(data->status);
	else if (WIFSIGNALED(data->status))
		data->status = WTERMSIG(data->status);
}

/* void	wait_process(t_shell *data) // no funciona con wait
{
 	if (wait(&data->status) == -1)
		perror("Error: wait failed");
	else
	{ 
		if (WIFEXITED(data->status))
			data->status = WEXITSTATUS(data->status);
		else if (WIFSIGNALED(data->status))
			data->status = WTERMSIG(data->status);
	}
} */

void	exec_one_cmd(t_shell *data, t_cmd *cmd)
{
	set_fdin(data, cmd);
	if (!execute_some_builtin(data, cmd))
	{
		data->pid = fork();
		if (data->pid < 0)
			perror("Error: fork failed");
		else if (data->pid == 0)
		{
			set_fdout(data, cmd);
			if (!execute_builtin_forked(data, cmd))
			{
				get_path(data, cmd);
				if (!data->path)
				{
					perror("Error: command not found");
					exit(127);
				}
				execve(data->path, cmd->arg, data->envp);
				perror("Error: execve failed");
				exit(1);
			}
		}
		else
			close(cmd->fdout);
		waitpid(data->pid, &(data->status), 0);
		get_status(data);
	}
}

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
		exec_multiple_cmds(data, current);
	restart_fds(data);
}
