#include "token.h"

Token	*create_token(TokenType type, const char *value, bool expect_arg)
{
	Token	*token;

	token = (Token *)malloc(sizeof(Token));
	if (!token)
	{
		ft_error(E_MEMORY, NULL, NULL);
		return (NULL);
	}
	token->type = type;
	token->value = ft_strdup(value);
	token->expect_arg = expect_arg;
	return (token);
}

void	free_token(Token **token)
{
	if (*token)
	{
		if ((*token)->value)
			free((*token)->value);
		free(*token);
	}
	*token = NULL;
}

int	verify_tokens(t_shell *data)
{
	int	balance_parentheses;
	int	balance_quotes;
	int	i;

	i = -1;
	balance_parentheses = 0;
	while (data->tokens && ++i < data->num_tokens)
	{
		if (data->tokens[i]->type == T_PAREN_OPEN)
			balance_parentheses++;
		else if (data->tokens[i]->type == T_PAREN_CLOSE)
			balance_parentheses--;
	}
	if (balance_parentheses < 0)
		ft_error(E_SYNTAX, "A parenthesis has not been opened", &data->status);
	else if (balance_parentheses > 0)
		ft_error(E_SYNTAX, "A parenthesis has not been closed", &data->status);
	i = -1;
	balance_quotes = 0;
	while (data->tokens && ++i < data->num_tokens)
		if (data->tokens[i]->type == T_QUOTE)
			balance_quotes++;
	if (balance_quotes % 2 != 0)
		ft_error(E_SYNTAX, "Invalid number of quotes", &data->status);
	return (balance_parentheses | balance_quotes % 2);
}

Token	**tokenize(t_shell *data)
{
	char	*input_copy;
	char	*start;
	char	*input;

	input = preprocess_input(data->prompt, data->status);
	data->tokens = (Token **)malloc(MAX_TOKENS * sizeof(Token *));
	if (!data->tokens)
	{
		ft_error(E_MEMORY, NULL, &data->status);
		return (NULL);
	}
	data->num_tokens = 0;
	input_copy = ft_strdup(input);
	start = input_copy;
	while (*start)
	{
		skip_delimiters(&start);
		if (!*start)
			break ;
		if (*start == '"' || *start == '\'')
			handle_quotes(&start, data->tokens, &data->num_tokens, *start);
		else
			if (handle_regular_tokens(&start, data) != 0)
				return (NULL);
	}
	free(input_copy);
	free(input);
	return (data->tokens);
}
