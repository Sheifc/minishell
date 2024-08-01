#include "minishell.h"

int	only_spaces(char *prompt)
{
	int	i;

	i = 0;
	while (prompt[i])
	{
		if (prompt[i] != ' ')
			return (0);
		i++;
	}
	return (1);
}
