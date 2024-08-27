/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sheferna <sheferna@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 19:23:26 by sheferna          #+#    #+#             */
/*   Updated: 2024/08/23 19:23:27 by sheferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_shell(t_shell *data, char **envp)
{
	data->cmd = NULL;
	data->env = NULL;
	data->export = NULL;
	data->prompt = NULL;
	data->envp = envp;
	data->path = NULL;
	data->status = 0;
	data->total_status = 0;
	data->pid = 0;
	data->cmd_count = 0;
}

void	init(t_shell *data, char **envp)
{
	init_signals();
	init_shell(data, envp);
	init_env(data, envp);
}
