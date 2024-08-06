#include "minishell.h"

int	execute_builtin(t_shell *data, t_cmd *cmd, char *arg)
{
	//dprintf(2, "\n***entra en execute_builtin***\n\n");
	//dprintf(2, "cmd->arg[0]: %s\n", cmd->arg[0]);
	if (data->cmd->n_args == 0)
		return (0);
	if (!ft_strncmp(arg, "echo\0", 5))
		return (ft_echo(data, cmd), 1);
	else if (!ft_strncmp(arg, "pwd\0", 4))
		return (ft_pwd(data), 1);
	else if (!ft_strncmp(arg, "cd\0", 3))
		return (ft_cd(data, cmd), 1);
	else if (!ft_strncmp(arg, "export\0", 7))
		return (ft_export(data, cmd), 1);
	else if (!ft_strncmp(arg, "unset\0", 6))
		return (ft_unset(data), 1);
	else if (!ft_strncmp(arg, "env\0", 4))
		return (ft_env(data, data->env), 1);
	else if (!ft_strncmp(arg, "exit\0", 5))
		return (ft_exit(cmd), 1);
	else
		return (0);
}

/* int	execute_builtin_forked(t_shell *data, t_cmd *cmd)
{
	if (data->cmd->n_args == 0)
		return (0);
	if (!ft_strncmp(data->cmd->arg[0], "echo\0", 5))
	{
		ft_echo(cmd);
		exit(0);
	}
	else if (!ft_strncmp(data->cmd->arg[0], "pwd\0", 4))
	{
		ft_pwd();
		exit(0);
	}
	else
		return (0);
}

int	execute_some_builtin(t_shell *data, t_cmd *cmd)
{
	if (data->cmd->n_args == 0)
		return (0);
	if (!ft_strncmp(data->cmd->arg[0], "cd\0", 3))
		return (ft_cd(data, cmd), 1);
	else if (!ft_strncmp(data->cmd->arg[0], "export\0", 7))
		return (ft_export(data), 1);
	else if (!ft_strncmp(data->cmd->arg[0], "unset\0", 6))
		return (ft_unset(data), 1);
	else if (!ft_strncmp(data->cmd->arg[0], "env\0", 4))
		return (ft_env(data->env), 1);
	else if (!ft_strncmp(data->cmd->arg[0], "exit\0", 5))
		return (ft_exit(cmd), 1);
	else
		return (0);
}

int	execute_builtin_all_forked(t_shell *data, t_cmd *cmd)
{
	if (data->cmd->n_args == 0)
		return (0);
	if (!ft_strncmp(data->cmd->arg[0], "echo\0", 5))
	{
		ft_echo(cmd);
		exit(0);
	}
	else if (!ft_strncmp(data->cmd->arg[0], "pwd\0", 4))
	{
		ft_pwd();
		exit(0);
	}
	else if (!ft_strncmp(data->cmd->arg[0], "cd\0", 3))
	{
		ft_cd(data, cmd);
		exit(0);
	}
	else if (!ft_strncmp(data->cmd->arg[0], "export\0", 7))
	{
		ft_export(data);
		exit(0);
	}
	else if (!ft_strncmp(data->cmd->arg[0], "unset\0", 6))
	{
		ft_unset(data);
		exit(0);
	}
	else if (!ft_strncmp(data->cmd->arg[0], "env\0", 4))
	{
		ft_env(data->env);
		exit(0);
	}
	else if (!ft_strncmp(data->cmd->arg[0], "exit\0", 5))
	{
		ft_exit(cmd);
		exit(0);
	}
	else
		return (0);
} */