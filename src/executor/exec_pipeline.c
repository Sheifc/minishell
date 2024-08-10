#include "minishell.h"

void	run_cmd(t_shell *data, t_cmd *cmd)
{
	dprintf(2, "entra en run_cmd\n");
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
		exit(1);
	}
	return (pid);
}

void	last_cmd(t_cmd *cmd, int fdpipe[2])
{
	close(fdpipe[1]);
	if (cmd->redirect == R_INFILE || cmd->redirect == R_OUTFILE)
	{
		redir_from_infile_if_needed(cmd);
		redir_to_outfile_if_needed(cmd);
	}
	else
	{
		if (dup2(fdpipe[0], 0) == -1)
		{
			perror("Error: dup2 failed for fdpipe[1]");
			exit(1);
		}
	}
	close(fdpipe[0]);
}

void	child_process(t_shell *data, t_cmd *cmd, int fdpipe[2])
{
	if (cmd->operator == NODE_PIPE)
	{
		if (cmd->redirect == R_INFILE)
			redir_from_infile_if_needed(cmd);
		close(fdpipe[0]);
		if (dup2(fdpipe[1], 1) == -1)
		{
			perror("Error: dup2 failed for fdpipe[1]");
			exit(1);
		}
		close(fdpipe[1]);
	}
 	else if (cmd->operator == NODE_END)
		last_cmd(cmd, fdpipe);
	run_cmd(data, cmd);
	exit(0);
}

void	close_fds(t_cmd *cmd)
{
	if (cmd->fdin != -1 && cmd->fdin != 0)
		close(cmd->fdin);
	if (cmd->fdout != -1 && cmd->fdout != 1)
		close(cmd->fdout);
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
		close_fds(cmd);
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
	dprintf(2, "entra en redir\n");
	if (save_fork() == 0)
	{
		redir_from_infile_if_needed(cmd);
		redir_to_outfile_if_needed(cmd);
		run_cmd(data, cmd);
		exit(0);
	}
	close(cmd->fdin);
	close(cmd->fdout);
	wait_process(data);
	if (cmd->next)
		exec_multiple_cmds(data, cmd->next);
}



void exec_multiple_cmds(t_shell *data, t_cmd *cmd)
{
	dprintf(2, "entra en multiple cmds\n");
	if (cmd->operator == NODE_OR || cmd->operator == NODE_AND)
		exec_bonus(data, &cmd);
  	else if (cmd->redirect == R_OUTFILE)
		exec_redir(data, cmd);
	else if (cmd->operator == NODE_PIPE || cmd->operator == NODE_END)
		exec_pipe(data, cmd);
}
