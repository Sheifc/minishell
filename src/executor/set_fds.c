#include "minishell.h"

void	fdin(t_cmd *cmd)
{
	if (cmd->fdin != -1 && cmd->fdin != 0)
	{
		if (dup2(cmd->fdin, 0) == -1)
		{
			perror("minishell: error: dup2");
			exit(EXIT_FAILURE);
		}
		close(cmd->fdin);
	}
}

void	fdout(t_cmd *cmd)
{
	if (cmd->fdout != -1 && cmd->fdout != 1)
	{
		if (dup2(cmd->fdout, 1) == -1)
		{
			perror("minishell: error: dup2");
			exit(EXIT_FAILURE);
		}
		close(cmd->fdout);
	}
}


