#include "minishell.h"

static void	print_cmd(t_cmd *cmd, int i, int newline)
{
	while (cmd->arg[i])
	{
		printf("%s", cmd->arg[i]);
		if (cmd->arg[i + 1])
			printf(" ");
		i++;
	}
	if (newline)
		printf("\n");
}

void	ft_echo(t_shell *data, t_cmd *cmd)
{
	int	i;
	int	j;
	int	newline;

	i = 1;
	j = 1;
	newline = 1;
	while (cmd->arg[i] && cmd->arg[i][0] == '-')
	{
		i++;
		while (cmd->arg[1][j] == 'n')
		{
			newline = 0;
			j++;
		}
		if (cmd->arg[1][j] != '\0')
		{
			newline = 1;
			i--;
			break ;
		}
	}
	print_cmd(cmd, i, newline);
	data->status = 0;
}
