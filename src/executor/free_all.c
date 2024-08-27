/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sheferna <sheferna@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 19:23:07 by sheferna          #+#    #+#             */
/*   Updated: 2024/08/23 19:23:08 by sheferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_all(t_shell *data)
{
	free(data->path);
	data->path = NULL;
	if (data->prompt)
		free(data->prompt);
	data->prompt = NULL;
	if (data->env)
		free_env_list(data->env);
	data->env = NULL;
	if (data->export)
		free_env_list(data->export);
	data->export = NULL;
	if (data->cmd)
		free_commands(&data->cmd);
	if (data->ast)
		free_ast(&data->ast);
}
