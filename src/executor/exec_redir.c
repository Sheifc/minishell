/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sheferna <sheferna@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 19:22:25 by sheferna          #+#    #+#             */
/*   Updated: 2024/08/23 19:22:26 by sheferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	run_cmd(t_shell *data, t_cmd *cmd)
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
		if (execve(data->path, cmd->arg, data->envp) < 0)
			ft_perror_exit("error: execve", data);
	}
}

void	redir_fdin(t_shell *data, t_cmd *cmd)
{
	if (cmd->fdin != -1 && cmd->fdin != 0)
	{
		if (dup2(cmd->fdin, 0) == -1)
			ft_perror_exit("error: dup2", data);
	}
}

void	redir_fdout(t_shell *data, t_cmd *cmd)
{
	if (cmd->fdout != -1 && cmd->fdout != 1)
	{
		if (dup2(cmd->fdout, 1) == -1)
			ft_perror_exit("error: dup2", data);
	}
}

void	exec_redir(t_shell *data, t_cmd *cmd)
{
	if (save_fork(data) == 0)
	{
		redir_fdin(data, cmd);
		redir_fdout(data, cmd);
		run_cmd(data, cmd);
		exit(0);
	}
	wait_process(data);
	close(cmd->fdin);
	close(cmd->fdout);
	if (cmd->next)
		exec_multiple_cmds(data, cmd->next);
}
