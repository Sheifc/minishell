/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_handles.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sheferna <sheferna@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 18:47:53 by sheferna          #+#    #+#             */
/*   Updated: 2024/08/27 18:47:54 by sheferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
void	handle_quotes(char **start, char **end)
{
	bool			in_quote;
	char			quote;

	skip_delimiters(start);
	in_quote = false;
	*end = *start;
	quote = -1;
	while (**end && ((!ft_strchr(DELIMITERS, **end) && **end != '('
				&& **end != ')' && **end != '|' && **end != '<' && **end != '>'
				&& **end != ';' && ft_strncmp(*end, "&&", 2) != 0
				&& ft_strncmp(*end, "||", 2) != 0
				&& ft_strncmp(*end, "<<", 2) != 0
				&& ft_strncmp(*end, ">>", 2) != 0)
			|| in_quote))
	{
		if ((**end == '"' || **end == '\'') && (!in_quote || **end == quote))
		{
			quote = **end;
			in_quote = !in_quote;
		}
		(*end)++;
	}
}

int	handle_redirect_arg(char **start, t_shell *data)
{
	char	*end;
	char	*value;
	int		size;

	skip_delimiters(start);
	if (*start[0] == '\0')
		return (0);
	end = *start;
	if (*end && (*end == '('
			|| *end == ')' || *end == '|' || *end == '<' || *end == '>'
			|| *end == ';' || ft_strncmp(end, "||", 2) == 0
			|| ft_strncmp(end, "||", 2) == 0
			|| ft_strncmp(end, "<<", 2) == 0
			|| ft_strncmp(end, ">>", 2) == 0))
	{
		size = get_operation_size(end);
		value = ft_strndup(end, size);
		ft_error_syntax(E_SYNTAX, value, "syntax error near unexpected",
			&data->status);
		free(value);
		return (1);
	}
	handle_quotes(start, &end);
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
