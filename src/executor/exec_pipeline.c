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
	redir_to_infile_if_needed(cmd);
	if (cmd->operator == NODE_PIPE)
	{
		close(fdpipe[0]);
		if (cmd->fdout != -1)
			redir_to_outfile_if_needed(cmd);
		else
		{
			if (dup2(fdpipe[1], STDOUT_FILENO) == -1)
			{
				perror("Error: dup2 failed for fdpipe[1]");
				exit(EXIT_FAILURE);
			}
			close(fdpipe[1]);
		}
	}
	else
		redir_to_outfile_if_needed(cmd);
	run_cmd(data, cmd);
	exit(EXIT_SUCCESS);
}

void	close_fds(t_cmd *cmd)
{
	if (cmd->fdin != -1 && cmd->fdin != 0)
		close(cmd->fdin);
	if (cmd->fdout != -1 && cmd->fdout != 1)
		close(cmd->fdout);
}

void	exec_multiple_cmds(t_shell *data, t_cmd *cmd)
{
	int		fdpipe[2];

	if (!cmd)
		return ;
	if (cmd->operator == NODE_PIPE)
	{
		if (pipe(fdpipe) < 0)
		{
			perror("Error: pipe failed");
			exit(EXIT_FAILURE);
		}
	}
	if (save_fork() == 0)
		child_process(data, cmd, fdpipe);
	else
	{
		close(fdpipe[1]);
		close_fds(cmd);
		if (cmd->next)
		{
			cmd->next->fdin = fdpipe[0];
			exec_multiple_cmds(data, cmd->next);
		}
		else
			close(fdpipe[0]);
		wait_process(data);
	}
}
