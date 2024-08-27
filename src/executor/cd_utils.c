/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sheferna <sheferna@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 19:20:25 by sheferna          #+#    #+#             */
/*   Updated: 2024/08/23 19:20:27 by sheferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	multiple_args(t_shell *data, t_cmd *cmd)
{
	if (cmd->n_args > 2)
	{
		ft_putstr_fd("minishell: cd: too many arguments\n", 2);
		data->status = 1;
		return (1);
	}
	return (0);
}

void	free_pwd(char *old_pwd, char *new_pwd)
{
	if (old_pwd)
		free(old_pwd);
	if (new_pwd)
		free(new_pwd);
}

void	update_status(t_shell *data)
{
	if (data->status == 1)
		data->status = 1;
	else
		data->status = 0;
}
