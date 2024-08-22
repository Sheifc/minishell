#include "minishell.h"

static void	access_cmd(t_shell *data, t_cmd *cmd)
{
	if (access(cmd->arg[0], X_OK) == 0)
	{
		data->path = cmd->arg[0];
		return ;
	}
}

void	get_path(t_shell *data, t_cmd *cmd)
{
	char	**content_splited;
	int		i;
	char	*path;
	char	*path_temp;
	char	*content;

	i = -1;
	access_cmd(data, cmd);
	content = get_value(data->env, "PATH");
	if (!content)
		return ;
	content_splited = ft_split(content, ':');
	while (content_splited[++i] != NULL)
	{
		path_temp = ft_strjoin(content_splited[i], "/");
		path = ft_strjoin(path_temp, cmd->arg[0]);
		free(path_temp);
		if (access(path, X_OK) == 0)
		{
			data->path = path;
			ft_free_matrix(content_splited);
			return ;
		}
		free(path);
	}
	ft_free_matrix(content_splited);
	return ;
}
