#include "minishell.h"

void	free_all(t_shell *data)
{
	if (data->prompt)
	{
		free(data->prompt);
		data->prompt = NULL;
	}
	if (data->env)
	{
		free_env_list(data->env);
		data->env = NULL;
	}
	if (data->export)
	{
		free_env_list(data->export);
		data->export = NULL;
	}
	if (data->cmd)
		free_commands(&data->cmd);
}
