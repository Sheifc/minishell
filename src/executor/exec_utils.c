/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sheferna <sheferna@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 19:22:34 by sheferna          #+#    #+#             */
/*   Updated: 2024/08/23 19:22:36 by sheferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	count_commands(t_shell *data)
{
	t_cmd	*current_cmd;

	current_cmd = data->cmd;
	data->cmd_count = 0;
	while (current_cmd != NULL)
	{
		data->cmd_count++;
		current_cmd = current_cmd->next;
	}
}

void	save_pipe(int *fdpipe)
{
	if (pipe(fdpipe) < 0)
	{
		perror("minishell: error: pipe");
		return ;
	}
}

pid_t	save_fork(t_shell *data)
{
	data->pid = fork();
	if (data->pid == -1)
	{
		perror("minishell: error: fork");
		exit(1);
	}
	return (data->pid);
}

pid_t	saved_fork(void)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		perror("minishell: error: fork failed");
		exit(1);
	}
	return (pid);
}

void	wait_pid(pid_t pid, t_shell *data)
{
	waitpid(pid, &(data->status), 0);
	get_status(data);
}
