#include "token.h"

// Function to create the wildcard token
void	handle_wildcards(char **start, Token **tokens, int *n_tokens)
{
	char	*end;
	char	temp;
	bool	found;

	end = *start;
	while (*end && !strchr(" \r\n\t\v\f\"'()|<>;&", *end))
		end++;
	temp = *end;
	*end = '\0';
	found = search_wildcard_matches(*start, tokens, n_tokens);
	if (found == false)
	{
		tokens[*n_tokens] = create_token(T_WILDCARD, *start, false);
		(*n_tokens)++;
	}
	*end = temp;
	*start = end;
}

// Function to create the text token
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
		token_value = ft_strndup(*start + 1, end - *start - 1);
		tokens[*n_tokens] = create_token(T_TEXT, token_value, false);
		(*n_tokens)++;
		*start = end + 1;
	}
	else
	{
		token_value = ft_strdup(*start + 1);
		tokens[*n_tokens] = create_token(T_TEXT, token_value, false);
		(*n_tokens)++;
		*start = end;
	}
	if (token_value)
		free(token_value);
}

// Main function for token matching
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
	else if (is_wildcards(start))
		handle_wildcards(start, tokens, n_tokens);
	else
		add_cmd_arg_token(start, tokens, n_tokens);
}
