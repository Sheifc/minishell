#include "minishell.h"

int	quote_stuff(int *i, char *prompt)
{
	int	quote_count;

	quote_count = 0;
	while (prompt[*i])
	{
		*i += 1;
		if (prompt[*i] == '\'')
			return (quote_count);
		else if (prompt[*i + 1] == '\0')
			return (-1);
		quote_count++;
	}
	return (0);
}

int	dquote_stuff(int *i, char *prompt)
{
	int	quote_count;

	quote_count = 0;
	while (prompt[*i])
	{
		*i += 1;
		if (prompt[*i] == '"')
			return (quote_count);
		else if (prompt[*i + 1] == '\0')
			return (-1);
		quote_count++;
	}
	return (0);
}
