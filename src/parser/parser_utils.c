#include "minishell.h"

int	only_spaces(char *prompt)
{
	int	i;

	i = 0;
	while (prompt[i])
	{
		if (prompt[i] != ' ' && prompt[i] != '\t')
			return (0);
		i++;
	}
	return (1);
}

int	only_wildcard(char *prompt)
{
	int i;

	i = 0;
	while (prompt[i])
	{
		if (prompt[i] != ' ' && prompt[i] != '\t' && prompt[i] != '*'
			&& prompt[i] != '?')
			return (0);
		i++;
	}
	return (1);
}