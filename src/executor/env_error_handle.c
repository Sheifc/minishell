/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_error_handle.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sheferna <sheferna@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 19:21:09 by sheferna          #+#    #+#             */
/*   Updated: 2024/08/23 19:21:11 by sheferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_env_other_errors(char *arg, t_shell *data)
{
	ft_putstr_fd("minishell: env: '", 2);
	ft_putstr_fd(arg, 2);
	ft_putendl_fd("': No such file or directory", 2);
	data->status = 127;
	return ;
}

void	handle_env_error(char *arg, t_shell *data)
{
	if (ft_strncmp(arg, "-\0", 2) == 0)
	{
		data->status = 0;
		return ;
	}
	if (arg[0] == '-' && ft_strlen(arg) > 1)
	{
		ft_putstr_fd("minishell: env: invalid option -- '", 2);
		ft_putstr_fd(&arg[1], 2);
		ft_putendl_fd("'", 2);
		ft_putendl_fd("Try 'env --help' for more information.", 2);
		data->status = 1;
		return ;
	}
	if (ft_strncmp(arg, ".\0", 2) == 0)
	{
		ft_putstr_fd("minishell: env: '", 2);
		ft_putstr_fd(arg, 2);
		ft_putendl_fd("': Permission denied", 2);
		data->status = 126;
		return ;
	}
	handle_env_other_errors(arg, data);
	return ;
}
