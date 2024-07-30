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
	token = NULL;
}

int	verify_tokens(Token **tokens, int *n_tokens)
{
	int	balance_parentheses;
	int	balance_quotes;
	int	i;

	i = -1;
	balance_parentheses = 0;
	while (tokens && ++i < *n_tokens)
	{
		if (tokens[i]->type == T_PAREN_OPEN)
			balance_parentheses++;
		else if (tokens[i]->type == T_PAREN_CLOSE)
			balance_parentheses--;
	}
	if (balance_parentheses < 0)
		printf("\e[31m ** Error parentesis: no se ha abierto **\e[0m\n");
	else if (balance_parentheses > 0)
		printf("\e[31m ** Error parentesis: no se ha cerrado **\e[0m\n");
	i = -1;
	balance_quotes = 0;
	while (tokens && ++i < *n_tokens)
		if (tokens[i]->type == T_QUOTE)
			balance_quotes++;
	if (balance_quotes % 2 != 0)
		printf("\e[31m ** Error quotes: el numero de commillas **\e[0m\n");
	return (balance_parentheses | balance_quotes % 2);
}

Token	**tokenize(const char *originalInput, int *n_tokens)
{
	Token	**tokens;
	char	*input_copy;
	char	*start;
	char	*input;

	input = preprocess_input(originalInput);
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
	if (input)
		free(input);
	return (tokens);
}
