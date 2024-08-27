/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_multi_cmds.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sheferna <sheferna@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 19:21:51 by sheferna          #+#    #+#             */
/*   Updated: 2024/08/23 19:21:52 by sheferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_multiple_cmds(t_shell *data, t_cmd *cmd)
{
	int	execution;

	execution = 0;
	if (!cmd)
		return ;
	if (cmd->parenthesis == 1 && cmd->parenthesis_status == P_OPEN)
		exec_parenthesis(data, cmd, &execution);
	else if (cmd->operator == NODE_OR || cmd->operator == NODE_AND)
		exec_bonus(data, cmd, &execution);
	else if (cmd->redirect == R_OUTFILE)
		exec_redir(data, cmd);
	else if (cmd->operator == NODE_PIPE || cmd->operator == NODE_END)
		exec_pipe(data, cmd);
}
