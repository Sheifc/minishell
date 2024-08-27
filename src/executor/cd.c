/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sheferna <sheferna@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 19:20:32 by sheferna          #+#    #+#             */
/*   Updated: 2024/08/23 19:20:33 by sheferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_new_pwd_and_update(t_shell *data, char *new_pwd,
	char *old_pwd, char *pwd)
{
	new_pwd = get_current_directory(data);
	if (!new_pwd)
	{
		free_pwd(old_pwd, pwd);
		return ;
	}
	if (update_variables(new_pwd, old_pwd, data->env))
	{
		free_pwd(old_pwd, new_pwd);
		return ;
	}
	if (update_variables(new_pwd, old_pwd, data->export))
	{
		free_pwd(old_pwd, new_pwd);
		return ;
	}
	free_pwd(old_pwd, new_pwd);
}

void	ft_cd(t_shell *data, t_cmd *cmd)
{
	char	*pwd;
	char	*old_pwd;
	char	*new_pwd;

	pwd = NULL;
	new_pwd = NULL;
	if (multiple_args(data, cmd))
		return ;
	old_pwd = get_current_directory(data);
	if (!old_pwd)
		return ;
	pwd = get_pwd(data, cmd, pwd);
	if (!pwd)
	{
		free(old_pwd);
		return ;
	}
	ft_chdir(data, pwd);
	handle_new_pwd_and_update(data, new_pwd, old_pwd, pwd);
	update_status(data);
}
