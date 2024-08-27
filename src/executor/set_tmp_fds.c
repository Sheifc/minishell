/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_tmp_fds.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sheferna <sheferna@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 19:24:17 by sheferna          #+#    #+#             */
/*   Updated: 2024/08/23 19:24:18 by sheferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_tmp_fds(t_shell *data)
{
	data->tmpin = dup(0);
	if (data->tmpin == -1)
	{
		perror("minishell: error: dup");
		return ;
	}
	data->tmpout = dup(1);
	if (data->tmpout == -1)
	{
		perror("minishel: error: dup");
		close(data->tmpin);
		return ;
	}
}

void	dup_fdin_tmp(t_shell *data, t_cmd *cmd)
{
	if (cmd->fdin == -1)
		cmd->fdin = dup(data->tmpin);
	if (cmd->fdin == -1)
	{
		perror("minishell: error: dup");
		return ;
	}
}

void	restart_fds(t_shell *data)
{
	dup2(data->tmpin, 0);
	dup2(data->tmpout, 1);
	close(data->tmpin);
	close(data->tmpout);
}
