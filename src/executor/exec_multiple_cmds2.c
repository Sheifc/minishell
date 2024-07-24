#include "minishell.h"

// void	set_fds_for_pipeline(t_shell *data, t_cmd *cmd, int is_first_cmd,
// 		int is_last_cmd)
// {
// 	if (is_first_cmd)
// 		set_fdin(data, cmd);
// 	if (!is_last_cmd)
// 	{
// 		if (dup2(cmd->fdout, 1) == -1)
// 		{
// 			perror("Error: dup2 failed for pipe write end");
// 			exit(EXIT_FAILURE);
// 		}
// 		close(cmd->fdout);
// 	}
// 	if (!is_first_cmd)
// 	{
// 		if (dup2(cmd->fdin, 0) == -1)
// 		{
// 			perror("Error: dup2 failed for fdin");
// 			exit(EXIT_FAILURE);
// 		}
// 		close(cmd->fdin);
// 	}
// 	if (is_last_cmd)
// 	{
// 		// if (dup2(cmd->fdout, 1) == -1)
// 		// {
// 		// 	perror("Error: dup2 failed for fdout");
// 		// 	close(cmd->fdout);
// 		// 	return ;
// 		// }
// 		close(cmd->fdout);
// 	}
// 		//set_fdout(data, cmd);
// }

// void	exec_multiple_cmds(t_shell *data, t_cmd *cmd)
// {
// 	pid_t pid;
// 	int pipefd[2];

// 	if (!cmd->next)
// 	{
// 		set_fds_for_pipeline(data, cmd, 0, 1);
// 		if (!execute_some_builtin(data, cmd))
// 		{
// 			data->pid = fork();
// 			if (data->pid < 0)
// 				perror("Error: fork failed");
// 			else if (data->pid == 0)
// 			{
// 				set_fdout(data, cmd);
// 				if (!execute_builtin_forked(data, cmd))
// 				{
// 					get_path(data, cmd);
// 					if (!data->path)
// 					{
// 						perror("Error: command not found");
// 						exit(127);
// 					}
// 					execve(data->path, cmd->arg, data->envp);
// 					perror("Error: execve failed");
// 					exit(1);
// 				}
// 			}
// 			else
// 			{
// 				close(cmd->fdout);
// 				waitpid(data->pid, &data->status, 0);
// 				data->status = WEXITSTATUS(data->status);
// 			}
// 		}
// 		return ;
// 	}

// 	if (pipe(pipefd) == -1)
// 	{
// 		perror("Error: pipe failed");
// 		exit(EXIT_FAILURE);
// 	}

// 	pid = fork();
// 	if (pid == -1)
// 	{
// 		perror("Error: fork failed");
// 		exit(EXIT_FAILURE);
// 	}
// 	else if (pid == 0)
// 	{
// 		close(pipefd[0]);
// 		cmd->fdout = pipefd[1];               
// 		set_fds_for_pipeline(data, cmd, 1, 0);
// 		if (!execute_some_builtin(data, cmd))
// 		{
// 			get_path(data, cmd);
// 			if (!data->path)
// 			{
// 				perror("Error: command not found");
// 				exit(127);
// 			}
// 			execve(data->path, cmd->arg, data->envp);
// 			perror("Error: execve failed");
// 			exit(1);
// 		}
// 		exit(EXIT_SUCCESS);
// 	}
// 	else
// 	{
// 		close(pipefd[1]);
// 		cmd->next->fdin = pipefd[0];   
// 		exec_multiple_cmds(data, cmd->next);
// 		waitpid(pid, &data->status, 0);
// 		data->status = WEXITSTATUS(data->status);
// 	}
// }
