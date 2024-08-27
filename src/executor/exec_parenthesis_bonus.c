/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_parenthesis_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sheferna <sheferna@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 19:22:05 by sheferna          #+#    #+#             */
/*   Updated: 2024/08/23 19:22:06 by sheferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	update_total_status(t_shell *data)
{
	if (data->status != 0)
		data->total_status = 1;
}

void	parenthesis_open(t_shell *data, t_cmd **cmd, int *execution)
{
	exec_one_cmd(data, *cmd);
	update_total_status(data);
	*execution = 1;
	if ((*cmd)->next)
	{
		if ((*cmd)->operator == NODE_AND && data->status == 0)
			*execution = 0;
		else if ((*cmd)->operator == NODE_OR && data->status != 0)
			*execution = 0;
		*cmd = (*cmd)->next;
		if ((*cmd)->parenthesis_status != P_CLOSE)
			parenthesis_open(data, cmd, execution);
		else if ((*cmd)->parenthesis_status == P_CLOSE)
			parenthesis_close(data, cmd, execution);
	}
}

void	parenthesis_close(t_shell *data, t_cmd **cmd, int *execution)
{
	if (*execution == 0)
	{
		exec_one_cmd(data, *cmd);
		update_total_status(data);
	}
	if ((*cmd)->next)
	{
		if ((*cmd)->operator == NODE_OR && data->total_status != 0)
			*execution = 0;
		else if ((*cmd)->operator == NODE_AND && data->total_status == 0)
			*execution = 0;
		else
			*execution = 1;
		*cmd = (*cmd)->next;
		exec_parenthesis(data, *cmd, execution);
	}
}

void	none_parenthesis(t_shell *data, t_cmd **cmd, int *execution)
{
	if ((*cmd) == NULL)
		return ;
	if ((*cmd)->operator == NODE_AND && data->status == 0)
		exec_node_and(data, *cmd, execution);
	else if ((*cmd)->operator == NODE_OR && data->status != 0)
		exec_node_or(data, *cmd, execution);
	else if ((*cmd)->parenthesis_status == P_OPEN && *execution == 0)
		exec_parenthesis(data, *cmd, execution);
	else if (*execution == 0)
		exec_one_cmd(data, *cmd);
	if ((*cmd)->next)
	{
		*cmd = (*cmd)->next;
		none_parenthesis(data, cmd, execution);
	}
}

void	exec_parenthesis(t_shell *data, t_cmd *cmd, int *execution)
{
	if (cmd != NULL)
	{
		if (cmd->parenthesis_status == P_OPEN && *execution == 0)
		{
			data->total_status = 0;
			parenthesis_open(data, &cmd, execution);
		}
		else if (cmd->parenthesis_status == P_CLOSE && *execution == 0)
			parenthesis_close(data, &cmd, execution);
		else if (cmd->parenthesis_status == P_NONE && *execution == 0)
			none_parenthesis(data, &cmd, execution);
	}
}
