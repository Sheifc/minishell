#include "minishell.h"

void	redir_to_infile_if_needed(t_cmd *cmd)
{
	if (cmd->fdin != -1 && cmd->fdin != 0)
	{
		if (dup2(cmd->fdin, 0) == -1)
		{
			perror("Error: dup2 failed for cmd->fdin");
			exit(EXIT_FAILURE);
		}
		close(cmd->fdin);
	}
}

void	redir_to_outfile_if_needed(t_cmd *cmd)
{
	if (cmd->fdout != -1 && cmd->fdout != 1)
	{
		if (dup2(cmd->fdout, 1) == -1)
		{
			perror("Error: dup2 failed for cmd->fdout");
			exit(EXIT_FAILURE);
		}
		close(cmd->fdout);
	}
}
