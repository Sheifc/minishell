#include "token.h"

// Function to create the wildcard token
void	handle_wildcards(char **start, Token **tokens, int *n_tokens)
{
	char	*end;
	char	temp;
	bool	found;

	end = *start;
	while (*end && !ft_strchr(" \r\n\t\v\f\"'()|<>;&", *end))
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

void	handle_unmatched_quotes(char **start, char *end, Token **tokens,
		int *n_tokens)
{
	char	*token_value;

	token_value = ft_strdup(*start + 1);
	tokens[(*n_tokens)++] = create_token(T_TEXT, token_value, false);
	if (token_value)
		free(token_value);
	*start = end;
}

// Function to create the text token
void	handle_quotes(char **start, Token **tokens, int *n_tokens,
		char quote_char)
{
	char	*end;
	char	*token_value;

	token_value = ft_strndup(*start, 1);
	tokens[(*n_tokens)++] = create_token(T_QUOTE, token_value, false);
	free(token_value);
	end = *start + 1;
	while (*end && *end != quote_char)
		end++;
	if (*end == quote_char)
	{
		if (*(end - 1) != quote_char)
		{
			token_value = ft_strndup(*start + 1, end - *start - 1);
			tokens[(*n_tokens)++] = create_token(T_TEXT, token_value, false);
			free(token_value);
		}
		token_value = ft_strndup(end, 1);
		tokens[(*n_tokens)++] = create_token(T_QUOTE, token_value, true);
		free(token_value);
		*start = end + 1;
	}
	else
		handle_unmatched_quotes(start, end, tokens, n_tokens);
}

void	handle_redirect_arg(char **start, Token **tokens, int *n_tokens)
{
	char		*end;
	char		temp;
	TokenType	type;

	end = *start + 1;
	while (*end && !ft_strchr(DELIMITERS, *end) && *end != '"' && *end != '\''
		&& *end != '(' && *end != ')' && *end != '|' && *end != '<'
		&& *end != '>' && *end != ';' && ft_strncmp(end, "&&", 2) != 0
		&& ft_strncmp(end, "||", 2) != 0 && ft_strncmp(end, "<<", 2) != 0
		&& ft_strncmp(end, ">>", 2) != 0)
		end++;
	if (end != *start + 1)
	{
		temp = *end;
		*end = '\0';
		type = T_REDIRECT_ARG;
		while (ft_strchr(DELIMITERS, **start))
			(*start)++;
		tokens[*n_tokens] = create_token(type, *start, true);
		(*n_tokens)++;
		*end = temp;
		*start = end;
	}
}

// Main function for token matching
void	handle_regular_tokens(char **start, Token **tokens, int *n_tokens)
{
	if (ft_strncmp(*start, "&&", 2) == 0)
		add_token(start, tokens, n_tokens, (Token){T_AND, "&&", false});
	else if (ft_strncmp(*start, "||", 2) == 0)
		add_token(start, tokens, n_tokens, (Token){T_OR, "||", false});
	else if (ft_strncmp(*start, "<<", 2) == 0)
		handle_heredoc_token(start, tokens, n_tokens);
	else if (ft_strncmp(*start, ">>", 2) == 0)
		handle_output_append_token(start, tokens, n_tokens);
	else if (**start == '|')
		add_token(start, tokens, n_tokens, (Token){T_PIPE, "|", false});
	else if (**start == '<')
		handle_input_token(start, tokens, n_tokens);
	else if (**start == '>')
		handle_output_token(start, tokens, n_tokens);
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
