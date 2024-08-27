/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sheferna <sheferna@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 19:21:43 by sheferna          #+#    #+#             */
/*   Updated: 2024/08/23 19:21:45 by sheferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_error_cmd(t_cmd *cmd)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd->arg[0], 2);
	ft_putendl_fd(": command not found", 2);
}

void	ft_perror_exit(char *str, t_shell *data)
{
	ft_putstr_fd("minishell: ", 2);
	perror(str);
	free_all(data);
	exit(1);
}
