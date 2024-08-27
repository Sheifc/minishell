/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_chdir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sheferna <sheferna@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 19:12:42 by sheferna          #+#    #+#             */
/*   Updated: 2024/08/23 19:12:51 by sheferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*env_lst_search(t_env *env, const char *key)
{
	t_env	*current;

	current = env;
	while (current)
	{
		if (!ft_strncmp(current->key, key, ft_strlen(key) + 1))
			return (current);
		current = current->next;
	}
	return (NULL);
}

char	*get_cd_value(t_env *env, const char *key)
{
	t_env	*node;

	if (env == NULL || key == NULL)
		return (NULL);
	node = env_lst_search(env, key);
	if (node)
		return (node->value);
	return (NULL);
}

char	*go_to(t_shell *data, char *location, char *error)
{
	char	*path;

	path = get_cd_value(data->env, location);
	if (!path)
	{
		ft_putendl_fd(error, 2);
		data->status = 1;
	}
	return (path);
}

char	*get_pwd(t_shell *data, t_cmd *cmd, char *path)
{
	if (cmd->n_args == 1 || !ft_strncmp(cmd->arg[1], "~\0", 2))
		path = go_to(data, "HOME", "minishell: cd: HOME not set");
	else if (!ft_strncmp(cmd->arg[1], "-\0", 2))
		path = go_to(data, "OLDPWD", "minishell: cd: OLDPWD not set");
	else
		path = cmd->arg[1];
	if (!path)
	{
		data->status = 1;
		return (NULL);
	}
	return (path);
}

int	ft_chdir(t_shell *data, char *pwd)
{
	if (chdir(pwd) < 0)
	{
		ft_putstr_fd("minishell: cd: ", 2);
		ft_putstr_fd(pwd, 2);
		ft_putendl_fd(": No such file or directory", 2);
		data->status = 1;
		return (1);
	}
	return (0);
}
