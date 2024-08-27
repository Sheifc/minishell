/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sheferna <sheferna@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 19:23:49 by sheferna          #+#    #+#             */
/*   Updated: 2024/08/23 19:23:51 by sheferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	access_cmd(t_shell *data, t_cmd *cmd)
{
	if (access(cmd->arg[0], X_OK) == 0)
	{
		data->path = cmd->arg[0];
		return ;
	}
}

static int	find_exec_path(char **content_splited, t_shell *data, t_cmd *cmd,
	int i)
{
	char	*path_temp;
	char	*path;

	path_temp = ft_strjoin(content_splited[i], "/");
	path = ft_strjoin(path_temp, cmd->arg[0]);
	free(path_temp);
	if (access(path, X_OK) == 0)
	{
		data->path = path;
		return (1);
	}
	free(path);
	return (0);
}

void	get_path(t_shell *data, t_cmd *cmd)
{
	char	**content_splited;
	int		i;
	char	*content;

	i = -1;
	access_cmd(data, cmd);
	if (data->path)
		return ;
	content = get_value(data->env, "PATH");
	if (!content)
		return ;
	content_splited = ft_split(content, ':');
	while (content_splited[++i] != NULL)
	{
		if (find_exec_path(content_splited, data, cmd, i))
			break ;
	}
	ft_free_matrix(content_splited);
	return ;
}
