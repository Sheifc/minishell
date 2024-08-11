#include "minishell.h"

int	run_cmd(t_shell *data, t_cmd *cmd)
{
	//dprintf(2, "entra en run_cmd\n");
	if (!execute_builtin(data, cmd, cmd->arg[0]))
	{
		get_path(data, cmd);
		if (!data->path)
		{
			perror("Error: command not found");
			return(127);
		}
		if (execve(data->path, cmd->arg, data->envp) < 0)
		{
			perror("Error: execve failed");
			return(errno);
		}
	}
	return (0);
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

void	close_fds(t_cmd *cmd)
{
	if (cmd->fdin != -1 && cmd->fdin != 0)
		close(cmd->fdin);
	if (cmd->fdout != -1 && cmd->fdout != 1)
		close(cmd->fdout);
}

int	exec_process(t_shell *data, t_cmd *cmd)
{
	int status = 0;

	if (cmd->redirect == R_INFILE)
	{
		if (dup2(cmd->fdin, 0) == -1)
		{
			perror("Error: dup2 failed for cmd->fdin");
			exit(1);
		}
	}
	if (cmd->redirect == R_OUTFILE)
	{
		if (dup2(cmd->fdout, 1) == -1)
		{
			perror("Error: dup2 failed for cmd->fdout");
			exit(1);
		}
	}
	status = run_cmd(data, cmd);
	exit(status);
}

void	exec_pipe(t_shell *data, t_cmd *cmd)
{
	int		fdpipe[2];

	if (pipe(fdpipe) < 0)
	{
		perror("Error: pipe failed");
		exit(1);
	}
	if (cmd->fdout == -1)
		ft_memcpy(&(cmd->fdout), fdpipe + 1, sizeof(int));
	else
		close(fdpipe[1]);
	if (cmd->next)
	{
		if (cmd->next->fdin == -1)
			ft_memcpy(&(cmd->next->fdin), fdpipe + 0, sizeof(int));
		else
			close(fdpipe[0]);
	}
	if (save_fork(data) == 0)
	{
		close(fdpipe[0]);
		close(fdpipe[1]);
		exit(exec_process(data, cmd));
	}
	else
	{
		wait_process(data);
		close(cmd->fdin);
		close(cmd->fdout);
		if (cmd->next)
			exec_multiple_cmds(data, cmd->next);
	}
}

void	exec_redir(t_shell *data, t_cmd *cmd)
{
	//dprintf(2, "entra en redir\n");
	if (save_fork(data) == 0)
	{
		redir_from_infile_if_needed(cmd);
		redir_to_outfile_if_needed(cmd);
		run_cmd(data, cmd);
		exit(0);
	}
	wait_process(data);
	close(cmd->fdin);
	close(cmd->fdout);
	if (cmd->next)
		exec_multiple_cmds(data, cmd->next);
}

void exec_multiple_cmds(t_shell *data, t_cmd *cmd)
{
	//dprintf(2, "entra en multiple cmds\n");
	if (!cmd)
		return ;
	if (cmd->operator == NODE_OR || cmd->operator == NODE_AND)
		exec_bonus(data, &cmd);
    else if (cmd->redirect == R_OUTFILE)
		exec_redir(data, cmd);
	else if (cmd->operator == NODE_PIPE || cmd->operator == NODE_END)
	{
		exec_pipe(data, cmd);
	}
}