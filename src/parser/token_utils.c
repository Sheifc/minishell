#include "token.h"

void	free_tokens(Token **tokens, int *num_tokens)
{
	int	i;

	if (tokens && *tokens)
	{
		i = -1;
		while (++i < *num_tokens)
		{
			free_token2(tokens[i]);
			tokens[i] = NULL;
		}
		free(*tokens);
	}
	*tokens = NULL;
	*num_tokens = 0;
}

void	skip_delimiters(char **start)
{
	while (**start && strchr(DELIMITERS, **start))
		(*start)++;
}

void	add_token(char **start, Token **tokens, int *n_tokens, Token t)
{
	tokens[*n_tokens] = create_token(t.type, t.value, t.expect_arg);
	(*n_tokens)++;
	*start += strlen(t.value);
}

void	add_cmd_arg_token(char **start, Token **tokens, int *n_tokens)
{
	char		*end;
	char		temp;
	TokenType	type;

	end = *start;
	while (*end && !strchr(DELIMITERS, *end) && *end != '"' && *end != '\''
		&& *end != '(' && *end != ')' && *end != '|' && *end != '<'
		&& *end != '>' && *end != ';' && strncmp(end, "&&", 2) != 0
		&& strncmp(end, "||", 2) != 0 && strncmp(end, "<<", 2) != 0
		&& strncmp(end, ">>", 2) != 0)
		end++;
	temp = *end;
	*end = '\0';
	if (*n_tokens > 0 && tokens[*n_tokens - 1]->expect_arg)
		type = T_ARG;
	else
		type = T_COMMAND;
	tokens[*n_tokens] = create_token(type, *start, true);
	(*n_tokens)++;
	*end = temp;
	*start = end;
}

void	print_tokens(Token **tokens, int n_tokens)
{
	int	i;

	i = -1;
	while (tokens && ++i < n_tokens)
		printf("Token %d: Type = %d, Value = %s\n", i, tokens[i]->type,
			tokens[i]->value);
}
