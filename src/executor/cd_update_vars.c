/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_update_vars.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sheferna <sheferna@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 19:20:16 by sheferna          #+#    #+#             */
/*   Updated: 2024/08/23 19:20:18 by sheferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	update_pwd(t_env *env, const char *key, char *value)
{
	t_env	*temp_env;

	temp_env = env_lst_search(env, key);
	if (temp_env)
	{
		free(temp_env->value);
		temp_env->value = ft_strdup(value);
		if (!temp_env->value)
			return (0);
	}
	return (1);
}

int	update_variables(char *new_pwd, char *old_pwd, t_env *list)
{
	if (!new_pwd)
	{
		perror("minishell: error: getting the new directory");
		return (1);
	}
	if (!update_pwd(list, "OLDPWD", old_pwd))
	{
		perror("minishell: error: updating OLDPWD");
		return (1);
	}
	if (!update_pwd(list, "PWD", new_pwd))
	{
		perror("minishell: error: updating PWD");
		return (1);
	}
	return (0);
}
