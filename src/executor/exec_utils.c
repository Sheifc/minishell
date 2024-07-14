#include "minishell.h"

void	ft_swap(char **a, char **b)
{
	char	*aux;

	aux = *a;
	*a = *b;
	*b = aux;
}

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

void	init_pid(t_shell *data)
{
	data->pid = ft_calloc(sizeof(int), data->cmd_count);
	if (!data->pid)
		perror("Error: malloc failed");
}

void	end_processess(int *pids, int len)
{
	while (len)
		kill(pids[--len], SIGKILL);
	free(pids);
}

void	wait_process(t_shell *data)
{
	while ((wait(&data->status)))
	{
		if (WIFEXITED(data->status))
			data->status = WEXITSTATUS(data->status);
		else if (WIFSIGNALED(data->status))
			data->status = WTERMSIG(data->status);
	}
}
