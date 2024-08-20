#include "token.h"

// Function to create the wildcard token
int	handle_wildcards(char **start, t_shell *data, t_token_type type)
{
	char	*end;
	char	temp;
	int		found;

	end = *start;
	while (*end && !ft_strchr(" \r\n\t\v\f\"'()|<>;&", *end))
		end++;
	temp = *end;
	*end = '\0';
	found = search_wildcard_matches(*start, data, type);
	if (found == -1)
		return (1);
	if (found == 0)
	{
		data->tokens[data->num_tokens] = create_token(type, *start, false,
				data);
		if (!data->tokens[data->num_tokens])
			return (1);
		data->num_tokens++;
	}
	*end = temp;
	*start = end;
	return (0);
}

void	handle_unmatched_quotes(char **start, char *end, t_shell *data)
{
	char	*token_value;

	token_value = ft_strdup(*start + 1);
	data->tokens[data->num_tokens++] = create_token(T_TEXT, token_value, false,
			data);
	if (token_value)
		free(token_value);
	*start = end;
}

// Function to create the text token
void	handle_quotes(char **start, t_shell *d, char quote_char)
{
	char	*end;
	char	*value;

	value = ft_strndup(*start, 1);
	add_token_and_free(d, T_QUOTE, value);
	end = *start + 1;
	while (*end && *end != quote_char)
		end++;
	if (*end == quote_char)
	{
		if (*(end - 1) != quote_char)
		{
			value = ft_strndup(*start + 1, end - *start - 1);
			handle_redirect_or_text_token(d, value);
			free(value);
		}
		else
			handle_redirect_or_text_token(d, " ");
		value = ft_strndup(end, 1);
		d->tokens[d->num_tokens++] = create_token(T_QUOTE, value, true, d);
		free(value);
		*start = end + 1;
	}
	else
		handle_unmatched_quotes(start, end, d);
}

int	handle_redirect_arg(char **start, t_shell *data)
{
	char	*end;

	end = *start + 1;
	while (*end && !ft_strchr(DELIMITERS, *end) && *end != '"' && *end != '\''
		&& *end != '(' && *end != ')' && *end != '|' && *end != '<'
		&& *end != '>' && *end != ';' && ft_strncmp(end, "&&", 2) != 0
		&& ft_strncmp(end, "||", 2) != 0 && ft_strncmp(end, "<<", 2) != 0
		&& ft_strncmp(end, ">>", 2) != 0)
		end++;
	if (ft_strlen(end) == 0)
		return (0);
	return (add_redirect_token(data, start, end));
}

// Main function for token matching
int	handle_regular_tokens(char **start, t_shell *data)
{
	if (ft_strncmp(*start, "&&", 2) == 0)
		return (add_token(start, data, (t_token){T_AND, "&&", false}));
	else if (ft_strncmp(*start, "||", 2) == 0)
		return (add_token(start, data, (t_token){T_OR, "||", false}));
	else if (ft_strncmp(*start, "<<", 2) == 0)
		return (handle_token(start, data, T_HEREDOC, "<<"));
	else if (ft_strncmp(*start, ">>", 2) == 0)
		return (handle_token(start, data, T_OUTPUT_APPEND, ">>"));
	else if (**start == '|')
		return (add_token(start, data, (t_token){T_PIPE, "|", false}));
	else if (**start == '<')
		return (handle_token(start, data, T_INPUT, "<"));
	else if (**start == '>')
		return (handle_token(start, data, T_OUTPUT, ">"));
	else if (**start == ';')
		return (add_token(start, data, (t_token){T_SEMICOLON, ";", false}));
	else if (**start == '(')
		return (add_token(start, data, (t_token){T_PAREN_OPEN, "(", false}));
	else if (**start == ')')
		return (add_token(start, data, (t_token){T_PAREN_CLOSE, ")", false}));
	else if (is_wildcards(start))
		return (handle_wildcards(start, data, T_WILDCARD));
	else
		return (add_cmd_arg_token(start, data));
	return (1);
}
