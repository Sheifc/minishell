/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sheferna <sheferna@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 19:21:30 by sheferna          #+#    #+#             */
/*   Updated: 2024/08/23 19:21:32 by sheferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute_builtin(t_shell *data, t_cmd *cmd, char *arg)
{
	if (data->cmd->n_args == 0)
		return (0);
	if (!ft_strncmp(arg, "echo\0", 5))
		return (ft_echo(data, cmd), 1);
	else if (!ft_strncmp(arg, "pwd\0", 4))
		return (ft_pwd(data), 1);
	else if (!ft_strncmp(arg, "cd\0", 3))
		return (ft_cd(data, cmd), 1);
	else if (!ft_strncmp(arg, "export\0", 7))
		return (ft_export(data, cmd), 1);
	else if (!ft_strncmp(arg, "unset\0", 6))
		return (ft_unset(data), 1);
	else if (!ft_strncmp(arg, "env\0", 4))
		return (ft_env(data, data->env), 1);
	else if (!ft_strncmp(arg, "exit\0", 5))
		return (ft_exit(data, cmd), 1);
	else
		return (0);
}
