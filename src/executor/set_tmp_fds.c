#include "minishell.h"

void	set_tmp_fds(t_shell *data)
{
	data->tmpin = dup(0);
	if (data->tmpin == -1)
	{
		perror("Error: dup failed for tmpin");
		return ;
	}
	data->tmpout = dup(1);
	if (data->tmpout == -1)
	{
		perror("Error: dup failed for tmpout");
		close(data->tmpin);
		return ;
	}
}

void	dup_fdin_tmp(t_shell *data, t_cmd *cmd)
{
	if (cmd->fdin == -1)
		cmd->fdin = dup(data->tmpin);
	if (cmd->fdin == -1)
	{
		perror("Error: dup failed for fdin");
		return ;
	}
}

void	set_fdin(t_shell *data, t_cmd *cmd)
{
	if (cmd->fdin == -1)
		cmd->fdin = dup(data->tmpin);
	if (cmd->fdin == -1)
	{
		perror("Error: dup failed for fdout");
		return ;
	}
	if (dup2(cmd->fdin, 1) == -1)
	{
		perror("Error: dup2 failed for fdout");
		close(cmd->fdin);
		return ;
	}
	close(cmd->fdin);
}

void	set_fdout(t_shell *data, t_cmd *cmd)
{
	if (cmd->fdout == -1)
		cmd->fdout = dup(data->tmpout);
	if (cmd->fdout == -1)
	{
		perror("Error: dup failed for fdout");
		return ;
	}
	if (dup2(cmd->fdout, 1) == -1)
	{
		perror("Error: dup2 failed for fdout");
		close(cmd->fdout);
		return ;
	}
	close(cmd->fdout);
}

void	restart_fds(t_shell *data)
{
	dup2(data->tmpin, 0);
	dup2(data->tmpout, 1);
	close(data->tmpin);
	close(data->tmpout);
}
