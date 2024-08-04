#include "minishell.h"

void	run_single_cmd(t_shell *data, t_cmd *cmd)
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

/* void	exec_node_or(t_shell *data, t_cmd **cmd)
{
	exec_one_cmd(data, *cmd);
	if ((*cmd)->next && data->status != 0 && (*cmd)->operator == NODE_OR)
	{
		*cmd = (*cmd)->next;
		exec_node_or(data, cmd);
	}
}

void	exec_node_and(t_shell *data, t_cmd **cmd)
{
	exec_one_cmd(data, *cmd);
	if ((*cmd)->next && data->status == 0 && (*cmd)->operator == NODE_AND)
	{
		*cmd = (*cmd)->next;
		exec_node_and(data, cmd);
	}
} */

void	exec_node_or(t_shell *data, t_cmd *cmd)
{
	exec_one_cmd(data, cmd);
	if (cmd->next && data->status != 0 && cmd->operator == NODE_OR)
	{
		cmd = cmd->next;
		exec_node_or(data, cmd);
	}
}

void	exec_node_and(t_shell *data, t_cmd *cmd)
{
	exec_one_cmd(data, cmd);
	if (cmd->next && data->status == 0 && cmd->operator == NODE_AND)
	{
		cmd = cmd->next;
		exec_node_and(data, cmd);
	}
}

void	exec_multiple_cmds(t_shell *data, t_cmd *cmd)
{
	pid_t	pid;
	int		fdpipe[2];

	if (!cmd)
		return ;
	if (cmd != NULL && (cmd->operator == NODE_AND || cmd->operator == NODE_OR))
	{
		if (cmd->operator == NODE_AND)
		{
			exec_node_and(data, cmd);
		}
		else if (cmd->operator == NODE_OR)
		{
			exec_node_or(data, cmd);
		}
		else
			exec_multiple_cmds(data, cmd->next);
	}
	else if (cmd->operator != NODE_AND && cmd->operator != NODE_OR)
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
			if (cmd->next)
			{
				close(fdpipe[0]);
				if (cmd->fdout != -1)
				{
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
			if (cmd->fdout != -1)
				close(cmd->fdout);
			if (cmd->next)
			{
				cmd->next->fdin = fdpipe[0];
				exec_multiple_cmds(data, cmd->next);
			}
			else
				close(fdpipe[0]);
			waitpid(data->pid, &(data->status), 0);
			get_status(data);
		}
	}
}
