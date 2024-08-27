/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_one_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sheferna <sheferna@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 19:21:58 by sheferna          #+#    #+#             */
/*   Updated: 2024/08/23 19:22:00 by sheferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_status(t_shell *data)
{
	if (WIFEXITED(data->status))
		data->status = WEXITSTATUS(data->status);
}

void	wait_process(t_shell *data)
{
	waitpid(data->pid, &(data->status), 0);
	get_status(data);
}

void	exec_one_cmd(t_shell *data, t_cmd *cmd)
{
	set_up_fds(cmd);
	if (!execute_builtin(data, cmd, cmd->arg[0]))
	{
		data->pid = fork();
		if (data->pid < 0)
		{
			perror("minishell: error: fork");
			return ;
		}
		else if (data->pid == 0)
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
		else
			wait_process(data);
	}
}
