/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sheferna <sheferna@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 19:23:26 by sheferna          #+#    #+#             */
/*   Updated: 2024/08/27 05:08:01 by sheferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_shell(t_shell *data, char **envp)
{
	data->tokens = NULL;
	data->ast = NULL;
	data->cmd = NULL;
	data->env = NULL;
	data->export = NULL;
	data->prompt = NULL;
	data->envp = envp;
	data->path = NULL;
	data->status = 0;
	data->total_status = 0;
	data->num_tokens = 0;
	data->parenthesis = 0;
	data->tmpin = -1;
	data->tmpout = -1;
	data->pid = 0;
	data->cmd_count = 0;
}

void	init(t_shell *data, char **envp)
{
	init_signals();
	init_shell(data, envp);
	init_env(data, envp);
}
