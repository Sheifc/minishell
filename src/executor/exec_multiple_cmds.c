#include "minishell.h"

void	run_single_cmd(t_shell *data, t_cmd *cmd)
{
	if (!execute_builtin(data, cmd))
	{
		get_path(data, cmd);
		if (!data->path)
		{
			perror("Error: command not found");
			exit(127);
		}
		if (cmd->fdout != -1)
		{
			if (dup2(cmd->fdout, 1) == -1)
			{
				perror("dup2 failed for cmd->fdout");
				exit(EXIT_FAILURE);
			}
			close(cmd->fdout);
		}
		if (execve(data->path, cmd->arg, data->envp) < 0)
		{
			perror("Error: execve failed");
			exit(1);
		}
	}
}

void	exec_multiple_cmds(t_shell *data, t_cmd *cmd)
{
	pid_t	pid;
	int		fdpipe[2];

	if (!cmd)
		return ;
	if (cmd->fdin == -1)
		cmd->fdin = dup(data->tmpin);
	if (cmd->fdin == -1)
	{
		perror("dup failed for cmd->fdin");
		exit(EXIT_FAILURE);
	}
	if (pipe(fdpipe) < 0)
	{
		perror("pipe failed");
		exit(EXIT_FAILURE);
	}
	pid = fork();
	if (pid < 0)
	{
		perror("fork failed");
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
	{
		if (cmd->next)
		{
			close(fdpipe[0]);
			if (cmd->fdout != -1)
			{
				//dprintf(2, "cmd->arg[1]: %s\n", cmd->arg[1]);
				//dprintf(2, "cmd->fdout: %d\n", cmd->fdout);
				if (dup2(cmd->fdout, STDOUT_FILENO) == -1)
				{
					perror("dup2 failed for cmd->fdout");
					exit(EXIT_FAILURE);
				}
				close(cmd->fdout);
				close(fdpipe[1]);
			}
			else
			{
				if (dup2(fdpipe[1], 1) == -1)
				{
					perror("dup2 failed for fdpipe[1]");
					exit(EXIT_FAILURE);
				}
				close(fdpipe[1]);
			}
		}
		else
		{
			close(fdpipe[0]);
			close(fdpipe[1]);
			if (cmd->fdout != -1)
			{
				if (dup2(cmd->fdout, 1) == -1)
				{
					perror("dup2 failed for cmd->fdout");
					exit(EXIT_FAILURE);
				}
				close(cmd->fdout);
			}
		}
		if (dup2(cmd->fdin, 0) == -1)
		{
			perror("dup2 failed for cmd->fdin");
			exit(EXIT_FAILURE);
		}

		close(cmd->fdin);
		run_single_cmd(data, cmd);
		exit(EXIT_SUCCESS);
	}
	else
	{
		close(fdpipe[1]);
		close(cmd->fdout);
		if (cmd->fdin != -1)
			close(cmd->fdin);
		//dprintf(2, "cmd->fdout en el padre: %d\n", cmd->fdout);
		if (cmd->fdout != -1)
			close(cmd->fdout);
		if (cmd->next)
		{
			cmd->next->fdin = fdpipe[0];
			exec_multiple_cmds(data, cmd->next);
		}
		else
			close(fdpipe[0]);
		waitpid(pid, &(data->status), 0);
		data->status = WEXITSTATUS(data->status);
	}
}
