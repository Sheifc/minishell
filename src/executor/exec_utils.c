#include "minishell.h"

void	count_commands(t_shell *data)
{
	t_cmd	*current_cmd;

	current_cmd = data->cmd;
	data->cmd_count = 0;
	while (current_cmd != NULL)
	{
		data->cmd_count++;
		current_cmd = current_cmd->next;
	}
}

void	save_pipe(int *fdpipe)
{
	if (pipe(fdpipe) < 0)
	{
		perror("pipe failed");
		exit(EXIT_FAILURE);
	}
}

pid_t	save_fork(t_shell *data)
{
	data->pid = fork();
	if (data->pid == -1)
	{
		perror("Error: fork failed");
		exit(1);
	}
	return (data->pid);
}

pid_t	saved_fork(void)
{
	pid_t pid = fork();
	if (pid == -1)
	{
		perror("Error: fork failed");
		exit(1);
	}
	return (pid);
}

void	wait_pid(pid_t pid, t_shell *data)
{
	waitpid(pid, &(data->status), 0);
	data->status = WEXITSTATUS(data->status);
}
