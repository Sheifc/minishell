/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipeline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sheferna <sheferna@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 19:22:18 by sheferna          #+#    #+#             */
/*   Updated: 2024/08/27 16:57:17 by sheferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	run_single_cmd(t_shell *data, t_cmd *cmd)
{
	if (!execute_builtin(data, cmd, cmd->arg[0]))
	{
		get_path(data, cmd);
		if (!data->path)
		{
			ft_error_cmd(cmd);
			free_all(data);
			exit(127);
		}
		if (cmd->fdout != -1 && cmd->fdout != 0)
		{
			if (dup2(cmd->fdout, 1) == -1)
				ft_perror_exit("error: dup2", data);
			close(cmd->fdout);
		}
		if (execve(data->path, cmd->arg, data->envp) < 0)
			ft_perror_exit("error: execve", data);
	}
}

void	dup_fdpipe(int *fdpipe, t_shell *data)
{
	close(fdpipe[0]);
	if (dup2(fdpipe[1], 1) == -1)
		ft_perror_exit("error: dup2", data);
	close(fdpipe[1]);
}

void	exec_fork(t_shell *data, t_cmd *cmd, int *fdpipe)
{
	if (cmd->next)
		dup_fdpipe(fdpipe, data);
	else
	{
		close(fdpipe[0]);
		close(fdpipe[1]);
		if (cmd->fdout != -1)
		{
			if (dup2(cmd->fdout, 1) == -1)
				ft_perror_exit("error: dup2", data);
			close(cmd->fdout);
		}
	}
	if (dup2(cmd->fdin, 0) == -1)
		ft_perror_exit("error: dup2", data);
	close(cmd->fdin);
	run_single_cmd(data, cmd);
	free_all(data);
	exit(0);
}

void	exec_pipe(t_shell *data, t_cmd *cmd)
{
	pid_t	pid;
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
