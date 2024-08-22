#include "minishell.h"

void	get_status(t_shell *data)
{
	if (WIFEXITED(data->status))
		data->status = WEXITSTATUS(data->status);
}

void	wait_process(t_shell *data)
{
	waitpid(data->pid, &(data->status), 0);
	get_status(data);
}

void	ft_error_cmd(t_cmd *cmd)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd->arg[0], 2);
	ft_putendl_fd(": command not found", 2);
}

void	set_up_fds(t_cmd *cmd)
{
	fdin(cmd);
	fdout(cmd);
}

void	exec_one_cmd(t_shell *data, t_cmd *cmd)
{
	set_up_fds(cmd);
	if (!execute_builtin(data, cmd, cmd->arg[0]))
	{
		data->pid = fork();
		if (data->pid < 0)
			perror("minishell: error: fork");
		else if (data->pid == 0)
		{
			get_path(data, cmd);
			if (!data->path)
			{
				ft_error_cmd(cmd);
				free_all(data);
				exit(127);
			}
			if (execve(data->path, cmd->arg, data->envp) < 0)
			{
				perror("minishell: error: execve failed");
				exit(1);
			}
		}
		else
			wait_process(data);
	}
}
