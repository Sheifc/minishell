#include "minishell.h"

void	run_single_cmd(t_shell *data, t_cmd *cmd)
{
	if (!execute_builtin(data, cmd, cmd->arg[0]))
	{
		get_path(data, cmd);
		if (!data->path)
		{
			ft_error_cmd(cmd);
			exit(127);
		}
		if (cmd->fdout != -1 && cmd->fdout != 0)
		{
			if (dup2(cmd->fdout, 1) == -1)
			{ 
				perror("minishell: error: dup2");
				exit(1);
			}
			close(cmd->fdout);
		}
		if (execve(data->path, cmd->arg, data->envp) < 0)
		{
			perror("minishell: error: execve");
			exit(1);
		}
	}
}

void	dup_fdpipe(int *fdpipe)
{
	close(fdpipe[0]);
	if (dup2(fdpipe[1], 1) == -1)
	{
		perror("minishell: error: dup2");
		exit(1);
	}
	close(fdpipe[1]);
}

void	exec_fork(t_shell *data, t_cmd *cmd, int *fdpipe)
{
	if (cmd->next)
		dup_fdpipe(fdpipe);
	else
	{
		close(fdpipe[0]);
		close(fdpipe[1]);
		if (cmd->fdout != -1)
		{
			if (dup2(cmd->fdout, 1) == -1)
			{
				perror("minishell: error: dup2");
				exit(1);
			}
			close(cmd->fdout);
		}
	}
 	if (dup2(cmd->fdin, 0) == -1)
	{
		perror("minishell: error: dup2");
		exit(1);
	}
	close(cmd->fdin);
	run_single_cmd(data, cmd);
	exit(0);
}

void	exec_pipe(t_shell *data, t_cmd *cmd)
{
	pid_t		pid;
	int		fdpipe[2];

	if (!cmd)
		return ;
	dup_fdin_tmp(data, cmd);
	save_pipe(fdpipe);
	pid = saved_fork();
	if (pid == 0)
		exec_fork(data, cmd, fdpipe);
	else
	{
		close(fdpipe[1]);
		if (cmd->fdin != -1)
			close(cmd->fdin);
		if (cmd->next)
		{
			cmd->next->fdin = fdpipe[0];
			exec_multiple_cmds(data, cmd->next);
		}
		else
			close(fdpipe[0]);
		wait_pid(pid, data);
	}
}
