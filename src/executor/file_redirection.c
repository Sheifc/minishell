#include "minishell.h"

void	redir_from_infile_if_needed(t_cmd *cmd)
{
	
	//dprintf(2, "cmd->fdin: %d\n", cmd->fdin);
	if (cmd->fdin != -1 && cmd->fdin != 0)
	{
		dprintf(2, "entra en la redireccion de infile\n");
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
		dprintf(2, "entra en la redireccion de outfile\n");
		if (dup2(cmd->fdout, 1) == -1)
		{
			perror("Error: dup2 failed for cmd->fdout");
			exit(EXIT_FAILURE);
		}
		close(cmd->fdout);
	}
}
