/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_fds.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sheferna <sheferna@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 19:24:10 by sheferna          #+#    #+#             */
/*   Updated: 2024/08/23 19:24:11 by sheferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	fdin(t_cmd *cmd)
{
	if (cmd->fdin != -1 && cmd->fdin != 0)
	{
		if (dup2(cmd->fdin, 0) == -1)
		{
			perror("minishell: error: dup2");
			return ;
		}
		close(cmd->fdin);
	}
}

void	fdout(t_cmd *cmd)
{
	if (cmd->fdout != -1 && cmd->fdout != 1)
	{
		if (dup2(cmd->fdout, 1) == -1)
		{
			perror("minishell: error: dup2");
			return ;
		}
		close(cmd->fdout);
	}
}

void	set_up_fds(t_cmd *cmd)
{
	fdin(cmd);
	fdout(cmd);
}
