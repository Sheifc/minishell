#include "minishell.h"

int	execute_builtin(t_shell *data, t_cmd *cmd)
{
	if (data->cmd->n_args == 0)
		return (0);
	if (!ft_strncmp(data->cmd->arg[0], "echo\0", 5))
		return (ft_echo(cmd), 1);
	else if (!ft_strncmp(data->cmd->arg[0], "pwd\0", 4))
		return (ft_pwd(), 1);
	else if (!ft_strncmp(data->cmd->arg[0], "cd\0", 3))
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

/* void	execute_echo(t_shell *data, t_cmd *cmd) // para pruebas
{
	if (data->cmd->n_args == 0)
		return ;
	if (!ft_strncmp(data->cmd->arg[0], "echo\0", 5))
	{
		ft_echo(cmd);
		exit(0);
	}
	else
		return ;
} */

int	execute_builtin_forked(t_shell *data, t_cmd *cmd)
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
