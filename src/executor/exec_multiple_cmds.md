#include "minishell.h"

void	wait_processess(t_shell *data)
{
	while ((waitpid(data->pid, &data->status, 0)))
	{
		if (WIFEXITED(data->status))
			data->status = WEXITSTATUS(data->status);
		else if (WIFSIGNALED(data->status))
			data->status = WTERMSIG(data->status);
	}
}

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
		if (execve(data->path, cmd->arg, data->envp) < 0)
		{
			perror("Error: execve failed");
			exit(1);
		}
	}
}

void	exec_last_cmd(t_shell *data, t_cmd *cmd)
{
	//pid_t	pid;
	//int		fdpipe[2];

/* 	pid_t	pid;
	pid = fork();
	if (pid < 0)
	{
		perror("fork failed");
		exit(EXIT_FAILURE);
	}
	if (pid == 0)
	{ */
 		// if (dup2(cmd->fdin, 0) == -1)
		// {

		// 	perror("dup2 failed for fdin");
		// 	close(cmd->fdin);
		// 	exit(1);
		// }
		//close(cmd->fdin);
		//if (cmd->fdout != -1)
		// {
		// 	if (dup2(cmd->fdout, 1) == -1)
		// 	{
		// 		perror("dup2 failed for fdout");
		// 		close(cmd->fdout);
		// 		exit(1);
		// 	}
			//close(cmd->fdout);
		//}
		run_single_cmd(data, cmd); //
// 	}
	//else
	//{
		//close(cmd->fdin); //
// if (cmd->fdout != -1)
// close(cmd->fdout);
// waitpid(pid, &(data->status), 0);
//}
}

void	exec_multiple_cmds(t_shell *data, t_cmd *cmd)
{
	pid_t pid;
	int fdpipe[2];
	pid = 0;
	fdpipe[0] = 0;
	fdpipe[1] = 0;
	if (!cmd)
		return ;
	if (cmd->fdin == -1)
		cmd->fdin = dup(data->tmpin);
	if (!cmd->next)
		run_single_cmd(data, cmd);
		//exec_last_cmd(data, cmd);
	if (cmd->next)
	{
  		// if (dup2(cmd->fdin, 0) == -1)
		// {
		// 	perror("dup2 failed for fdin");
		// 	close(cmd->fdin);
		// 	exit(1);
		// }
		close(cmd->fdin);
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
			// close(fdpipe[0]);
			// if (dup2(fdpipe[1], 1) == -1)
			// {
			// 	perror("dup2 failed for fdpipe[1]");
			// 	exit(1);
			// }
			// close(fdpipe[1]);
			// run_single_cmd(data, cmd);
			close(fdpipe[0]);
			if (dup2(cmd->fdin, 0) == -1)
			{
				perror("dup2 failed for cmd->fdin");
				exit(EXIT_FAILURE);
			}
			close(cmd->fdin);

			if (dup2(fdpipe[1], 1) == -1)
			{
				perror("dup2 failed for fdpipe[1]");
				exit(EXIT_FAILURE);
			}
			close(fdpipe[1]);
			run_single_cmd(data, cmd);
			exit(EXIT_SUCCESS);
		}
		else
		{
			close(fdpipe[1]);
			if (cmd->fdin != -1)
				close(cmd->fdin);
			cmd->next->fdin = fdpipe[0];
			exec_multiple_cmds(data, cmd->next);
			waitpid(pid, &(data->status), 0);
			data->status = WEXITSTATUS(data->status);
		}
	}
}


void	exec_multiple_cmds(t_shell *data, t_cmd *cmd)
{
	pid_t pid;
	int fdpipe[2];
	pid = 0;
	fdpipe[0] = 0;
	fdpipe[1] = 0;
	if (!cmd)
		return ;
	if (cmd->fdin == -1)
		cmd->fdin = dup(data->tmpin);
	if (cmd->fdin == -1)
    {
        perror("dup failed for cmd->fdin");
        return ;
    }
	if (!cmd->next)
    {
        if (dup2(cmd->fdin, 0) == -1)
        {
            perror("dup2 failed for cmd->fdin");
            exit(EXIT_FAILURE);
        }
        close(cmd->fdin);
        run_single_cmd(data, cmd);
        return;
    }
	if (cmd->next)
	{
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
			close(fdpipe[0]);
			if (dup2(cmd->fdin, 0) == -1)
			{
				perror("dup2 failed for cmd->fdin");
				exit(EXIT_FAILURE);
			}
			close(cmd->fdin);

			if (dup2(fdpipe[1], 1) == -1)
			{
				perror("dup2 failed for fdpipe[1]");
				exit(EXIT_FAILURE);
			}
			close(fdpipe[1]);
			run_single_cmd(data, cmd);
			exit(EXIT_SUCCESS);
		}
		else
		{
			close(fdpipe[1]);
			if (cmd->fdin != -1)
				close(cmd->fdin);
			cmd->next->fdin = fdpipe[0];
			exec_multiple_cmds(data, cmd->next);
			waitpid(pid, &(data->status), 0);
			data->status = WEXITSTATUS(data->status);
		}
	}
}
