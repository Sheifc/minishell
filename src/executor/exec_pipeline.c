#include "minishell.h"

void	run_cmd(t_shell *data, t_cmd *cmd)
{
	if (!execute_builtin(data, cmd, cmd->arg[0]))
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
}

pid_t	save_fork(void)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		perror("Error: fork failed");
		exit(EXIT_FAILURE);
	}
	return (pid);
}

void	child_process(t_shell *data, t_cmd *cmd, int fdpipe[2])
{
	if (cmd->operator == NODE_PIPE)
	{
		close(fdpipe[0]);
		if (dup2(fdpipe[1], 1) == -1)
		{
			perror("Error: dup2 failed for fdpipe[1]");
			exit(1);
		}
		close(fdpipe[1]);
	}
	else if (cmd->operator == NODE_END)
	{
		close(fdpipe[1]);
		if (dup2(fdpipe[0], 0) == -1)
		{
			perror("Error: dup2 failed for fdpipe[1]");
			exit(1);
		}
		close(fdpipe[0]);
	}
	run_cmd(data, cmd);
	exit(0);
}

void	exec_pipe(t_shell *data, t_cmd *cmd)
{
	int		fdpipe[2];

	if (pipe(fdpipe) < 0)
	{
		perror("Error: pipe failed");
		exit(1);
	}
	if (save_fork() == 0)
		child_process(data, cmd, fdpipe);
	else
	{
		if (cmd->next)
		{
			close(fdpipe[1]);
			cmd->next->fdin = fdpipe[0];
			exec_pipe(data, cmd->next);
		}
		else
		{
			close(fdpipe[0]);
			close(fdpipe[1]);
		}
		wait_process(data);
	}
}

void	exec_redir(t_shell *data, t_cmd *cmd)
{
	if (cmd->redirect == R_INFILE)
		redir_to_infile_if_needed(cmd);
	else if (cmd->redirect == R_OUTFILE)
		redir_to_outfile_if_needed(cmd);
	exec_pipe(data, cmd);
}

void	close_fds(t_cmd *cmd)
{
	if (cmd->fdin != -1 && cmd->fdin != 0)
		close(cmd->fdin);
	if (cmd->fdout != -1 && cmd->fdout != 1)
		close(cmd->fdout);
}
