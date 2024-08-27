/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_and_or_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sheferna <sheferna@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 19:21:24 by sheferna          #+#    #+#             */
/*   Updated: 2024/08/23 19:21:25 by sheferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_node_or(t_shell *data, t_cmd *cmd, int *execution)
{
	if (*execution == 0)
	{
		exec_one_cmd(data, cmd);
		*execution = 1;
	}
	if (cmd->next && data->status != 0)
	{
		*execution = 0;
		exec_bonus(data, cmd->next, execution);
	}
}

void	exec_node_and(t_shell *data, t_cmd *cmd, int *execution)
{
	if (*execution == 0)
	{
		exec_one_cmd(data, cmd);
		*execution = 1;
	}
	if (cmd->next && data->status == 0)
	{
		*execution = 0;
		exec_bonus(data, cmd->next, execution);
	}
}

void	exec_bonus(t_shell *data, t_cmd *cmd, int *execution)
{
	if (cmd != NULL && cmd->parenthesis == 0)
	{
		if (cmd->operator == NODE_AND)
			exec_node_and(data, cmd, execution);
		else if (cmd->operator == NODE_OR)
			exec_node_or(data, cmd, execution);
		else if (cmd->operator == NODE_PIPE || cmd->operator == NODE_END)
			exec_multiple_cmds(data, cmd);
		else if (cmd->next)
			exec_bonus(data, cmd->next, execution);
	}
}
