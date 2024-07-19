#include "token.h"

Token	*create_token(TokenType type, const char *value, bool expect_arg)
{
	Token	*token;

	token = (Token *)malloc(sizeof(Token));
	token->type = type;
	token->value = strdup(value);
	token->expect_arg = expect_arg;
	return (token);
}

void	free_token2(Token *token)
{
	if (token)
	{
		free(token->value);
		free(token);
	}
}

Token	**tokenize(const char *input, int *n_tokens)
{
	Token	**tokens;
	char	*input_copy;
	char	*start;

	tokens = (Token **)malloc(MAX_TOKENS * sizeof(Token *));
	*n_tokens = 0;
	input_copy = ft_strdup(input);
	start = input_copy;
	while (*start)
	{
		skip_delimiters(&start);
		if (!*start)
			break ;
		if (*start == '"' || *start == '\'')
			handle_quotes(&start, tokens, n_tokens, *start);
		else
			handle_regular_tokens(&start, tokens, n_tokens);
	}
	free(input_copy);
	return (tokens);
}
