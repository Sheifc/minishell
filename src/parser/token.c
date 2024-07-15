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

void	handle_quotes(char **start, Token **tokens, int *n_tokens,
		char quote_char)
{
	char	*end;
	char	*token_value;

	end = *start + 1;
	while (*end && *end != quote_char)
		end++;
	if (*end == quote_char)
	{
		token_value = strndup(*start + 1, end - *start - 1);
		tokens[*n_tokens] = create_token(T_TEXT, token_value, false);
		(*n_tokens)++;
		*start = end + 1;
	}
	else
	{
		token_value = strdup(*start + 1);
		tokens[*n_tokens] = create_token(T_TEXT, token_value, false);
		(*n_tokens)++;
		*start = end;
	}
}

void	handle_regular_tokens(char **start, Token **tokens, int *n_tokens)
{
	if (strncmp(*start, "&&", 2) == 0)
		add_token(start, tokens, n_tokens, (Token){T_AND, "&&", false});
	else if (strncmp(*start, "||", 2) == 0)
		add_token(start, tokens, n_tokens, (Token){T_OR, "||", false});
	else if (strncmp(*start, "<<", 2) == 0)
		add_token(start, tokens, n_tokens, (Token){T_HEREDOC, "<<", true});
	else if (strncmp(*start, ">>", 2) == 0)
		add_token(start, tokens, n_tokens, (Token){T_OUTPUT_APPEND, ">>",
			true});
	else if (**start == '|')
		add_token(start, tokens, n_tokens, (Token){T_PIPE, "|", false});
	else if (**start == '<')
		add_token(start, tokens, n_tokens, (Token){T_INPUT, "<", true});
	else if (**start == '>')
		add_token(start, tokens, n_tokens, (Token){T_OUTPUT, ">", true});
	else if (**start == ';')
		add_token(start, tokens, n_tokens, (Token){T_SEMICOLON, ";", false});
	else if (**start == '(')
		add_token(start, tokens, n_tokens, (Token){T_PAREN_OPEN, "(", false});
	else if (**start == ')')
		add_token(start, tokens, n_tokens, (Token){T_PAREN_CLOSE, ")", false});
	else
		add_cmd_arg_token(start, tokens, n_tokens);
}

Token	**tokenize(const char *input, int *n_tokens)
{
	Token	**tokens;
	char	*input_copy;
	char	*start;

	tokens = (Token **)malloc(MAX_TOKENS * sizeof(Token *));
	*n_tokens = 0;
	input_copy = strdup(input);
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
