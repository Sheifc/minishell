#include "minishell.h"

void	ft_swap(char **a, char **b)
{
	char	*aux;

	aux = *a;
	*a = *b;
	*b = aux;
}

void	count_commands(t_shell *data)
{
	t_cmd	*current_cmd;

	current_cmd = data->cmd;
	data->cmd_count = 0;
	while (current_cmd != NULL)
	{
		data->cmd_count++;
		current_cmd = current_cmd->next;
	}
}

