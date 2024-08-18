#include "minishell.h"

void	run_cmd(t_shell *data, t_cmd *cmd)
{
	if (!execute_builtin(data, cmd, cmd->arg[0]))
	{
		get_path(data, cmd);
		if (!data->path)
		{
			perror("minishell: error: command not found");
			exit(127);
		}
		if (execve(data->path, cmd->arg, data->envp) < 0)
		{
			perror("minishell: error: execve");
			exit(1);
		}
	}
}

void	redir_fdin(t_cmd *cmd)
{
	if (cmd->fdin != -1 && cmd->fdin != 0)
	{
		if (dup2(cmd->fdin, 0) == -1)
		{
			perror("minishell: error: dup2");
			exit(1);
		}
	}
}

void	redir_fdout(t_cmd *cmd)
{
	if (cmd->fdout != -1 && cmd->fdout != 1)
	{
		if (dup2(cmd->fdout, 1) == -1)
		{
			perror("minishell: error: dup2");
			exit(1);
		}
	}
}

void	exec_redir(t_shell *data, t_cmd *cmd)
{
	if (save_fork(data) == 0)
	{
		redir_fdin(cmd);
		redir_fdout(cmd);
		run_cmd(data, cmd);
		exit(0);
	}
	wait_process(data);
	close(cmd->fdin);
	close(cmd->fdout);
	if (cmd->next)
		exec_multiple_cmds(data, cmd->next);
}
