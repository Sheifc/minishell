#include "minishell.h"

void	wait_process(t_shell *data)
{
	while ((wait(&data->status) > 0))
	{
		if (WIFEXITED(data->status))
			data->status = WEXITSTATUS(data->status);
		else if (WIFSIGNALED(data->status))
			data->status = WTERMSIG(data->status);
	}
}

void	redirection(t_cmd *current, int tmpout, int last_cmd)
{
	int	fdpipe[2];
	dprintf(2, "entra en redirection\n");
	dup2(current->fdin, 0);
	dprintf(2, "fdin before pipe en redirection: %d\n", current->fdin);
	close(current->fdin);
	if (last_cmd)
	{
		if (current->fdout == -1)
			current->fdout = dup(tmpout);
		dprintf(2, "fdout last command: %d\n", current->fdout);
	}
	else
	{
		pipe(fdpipe);
		dprintf(2, "fdin after pipe: %d\n", current->fdin);
		current->next->fdin = dup(fdpipe[0]);
		dprintf(2, "fdin next command after pipe: %d\n", current->next->fdin);
		close(fdpipe[0]);
		if (current->fdout == -1){
			current->fdout = dup(fdpipe[1]);
			dprintf(2, "fdout after pipe: %d\n", current->fdout);
			}
		else
			close(fdpipe[1]);
	}
	dup2(current->fdout, 1);
	close(current->fdout);
	dprintf(2, "fdout after redirection: %d\n", current->fdout);
}

void	executer(t_shell *data, t_cmd *current) //, int i
{
	if (!execute_builtin(data))
	{
		data->pid = fork();
		if (data->pid == 0)
		{
			get_path(data, current);
			if (!data->path)
			{
				perror("Error: command not found");
				exit(errno);
			}
			execve(data->path, current->arg, data->envp);
			perror("Error: execve failed");
			exit(errno);
		}
		else if (data->pid < 0)
			perror("Error: fork failed");
		else if (current != NULL){
			close(current->fdout);
			dprintf(2, "fdout if current != NULL en executer: %d\n", current->fdout);}
	}
}

void	restart_fds(int tmpin, int tmpout)
{
	dup2(tmpin, 0);
	dup2(tmpout, 1);
	dprintf(2, "tmpin: %d\n", tmpin);
	dprintf(2, "tmpout: %d\n", tmpout);
	close(tmpin);
	close(tmpout);
}

void	executor(t_shell *data)
{
	int		tmpin;
	int		tmpout;
	int		i;
	t_cmd	*current;

	i = -1;
	count_commands(data);
	current = data->cmd;
	if (!current)
		return ;
	tmpin = dup(0);
	tmpout = dup(1);
	dprintf(2, "tmpin: %d\n", tmpin);
	dprintf(2, "tmpout: %d\n", tmpout);
	if (current->fdin == -1)
		current->fdin = dup(tmpin);
	dprintf(2, "fdin if cmd->fdin == -1: %d\n", current->fdin);
	if (data->cmd_count == 1)
	{
		redirection(current, tmpout, 1);
		executer(data, current);
	}
	else
	{
		while (++i < data->cmd_count)
		{
			redirection(current, tmpout, data->cmd_count - 1 == i);
			executer(data, current);
			current = current->next;
		}
	}
	wait_process(data);
	restart_fds(tmpin, tmpout);
}
