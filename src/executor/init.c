#include "minishell.h"

void	init_shell(t_shell *data, char **envp)
{
	data->cmd = NULL;
	data->env = NULL;
	data->export = NULL;
	data->prompt = NULL;
	data->envp = envp;
	data->path = NULL;
	data->status = 0;
	data->total_status = 0;
	data->flag = 1;
	data->pid = 0;
	data->cmd_count = 0;
}

void	init(t_shell *data, char **envp)
{
	init_signals();
	init_shell(data, envp);
	init_env(data, envp);
}
