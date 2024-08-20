#include "token.h"

bool	is_operator(const char *str)
{
	return (ft_strcmp(str, "&&") == 0 || ft_strcmp(str, "||") == 0
		|| ft_strcmp(str, "|") == 0 || strcmp(str, ";") == 0);
}

int	handle_token(char **start, t_shell *data, t_token_type type,
	char *value)
{
	if (add_token(start, data, (t_token){type, value, true}) != 0)
		return (1);
	return (handle_redirect_arg(start, data));
}

void	handle_redirect_or_text_token(t_shell *data, char *token_value)
{
	if (data->num_tokens > 1
		&& (data->tokens[data->num_tokens - 2]->type == T_INPUT
			|| data->tokens[data->num_tokens - 2]->type == T_OUTPUT
			|| data->tokens[data->num_tokens - 2]->type == T_OUTPUT_APPEND
			|| data->tokens[data->num_tokens - 2]->type == T_HEREDOC))
		data->tokens[(data->num_tokens)++] = create_token(T_REDIRECT_ARG,
				token_value, false, data);
	else
		data->tokens[(data->num_tokens)++] = create_token(T_TEXT, token_value,
				false, data);
}

void	add_token_and_free(t_shell *data, t_token_type type,
	char *value)
{
	data->tokens[data->num_tokens++] = create_token(type, value, false, data);
	free(value);
}

int	add_redirect_token(t_shell *data, char **start, char *end)
{
	char	temp;

	temp = *end;
	*end = '\0';
	while (ft_strchr(DELIMITERS, **start))
		(*start)++;
	if (is_wildcards(start))
		return (handle_wildcards(start, data, T_REDIRECT_ARG));
	data->tokens[data->num_tokens] = create_token(T_REDIRECT_ARG, *start, true,
			data);
	if (!data->tokens[data->num_tokens])
		return (1);
	data->num_tokens++;
	*end = temp;
	*start = end;
	return (0);
}
