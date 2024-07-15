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
	int fdpipe[2];

	dup2(current->fdin, 0);
	close(current->fdin);
	if (last_cmd)
	{
		dprintf(2, "entra en last_cmd\n");
		if (current->fdout == -1)
			current->fdout = dup(tmpout);
	}
	else
	{
		dprintf(2, "entra en else\n");
		pipe(fdpipe);
		current->next->fdin = fdpipe[0];
		if (current->fdout == -1){
			current->fdout = fdpipe[1];
			dprintf(2, "escrito en pipe\n");}
		else{
			close(fdpipe[1]);
			dprintf(2, "cierro fdpipe[1]\n");}
	}
	dup2(current->fdout, 1);
	close(current->fdout);
}

void	executer(t_shell *data, t_cmd *current)
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
		else
		if (current != NULL)
			close(current->fdout);
	}
}

void restart_fds(int tmpin, int tmpout)
{	
	dup2(tmpin, 0);
	dup2(tmpout, 1);
	close(tmpin);
	close(tmpout);
}

void executor(t_shell *data)
{
	int tmpin;
	int tmpout;
	int i;
	t_cmd *current;

	i = -1;
	count_commands(data);
	current = data->cmd;
	if (!current)
		return ;
	tmpin = dup(0);
	tmpout = dup(1);
	if (current->fdin == -1)
		current->fdin = dup(tmpin);
	while (++i < data->cmd_count)
	{
		redirection(current, tmpout, data->cmd_count - 1 == i);
		executer(data, current);
		current = current->next;
	}
	wait_process(data);
	restart_fds(tmpin, tmpout);
}
