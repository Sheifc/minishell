#include "minishell.h"

void	get_status(t_shell *data)
{
	if (WIFEXITED(data->status))
		data->status = WEXITSTATUS(data->status);
	else if (WIFSIGNALED(data->status))
		data->status = WTERMSIG(data->status);
}

void	exec_one_cmd(t_shell *data, t_cmd *cmd)
{
	// printf("\e[0m - Ejecutando comando: \e[33m%s\e[0m -\e[32m\n", cmd->name);
	if (cmd->operator == NODE_END && (ft_strcmp(cmd->name, "save_outfile") == 0
		|| ft_strcmp(cmd->name, "save_append") == 0))
	{
		return ;
	}
	set_fdin(data, cmd);
	if (!execute_builtin(data, cmd))
	{
		if (ft_strcmp(cmd->name, "save_outfile") == 0
			|| ft_strcmp(cmd->name, "save_append") == 0)
		{
			cmd->name = ft_strdup("cat");
			cmd->arg[0] = ft_strdup("cat");
		}
		data->pid = fork();
		if (data->pid < 0)
			perror("Error: fork failed");
		else if (data->pid == 0)
		{
			set_fdout(data, cmd);
			get_path(data, cmd);
			if (!data->path)
			{
				perror("Error: command not found");
				exit(127);
			}
			// print_command(cmd);
			execve(data->path, cmd->arg, data->envp);
			perror("Error: execve failed");
			exit(1);
		}
		else{
			if (cmd->fdin != STDIN_FILENO)
			{
				close(cmd->fdin);
			}
			if (cmd->fdout != STDOUT_FILENO)
			{
				if (!cmd->next || cmd->next->fdout != cmd->fdout)
					close(cmd->fdout);
			}
		}
		if (cmd->operator != NODE_PIPE || cmd->fdout != 1)
			waitpid(data->pid, &(data->status), 0);
		get_status(data);
	}
	if (cmd->next)
		exec_one_cmd(data, cmd->next);
}

void	executor(t_shell *data)
{
	t_cmd	*current;

	count_commands(data);
	current = data->cmd;
	if (!current)
		return ;
	set_tmp_fds(data);
	// if (data->cmd_count == 1)
		exec_one_cmd(data, current);
	// else if (data->cmd_count > 1)
	// 	exec_multiple_cmds(data, current);
	free_commands(&data->cmd);
	restart_fds(data);
}
