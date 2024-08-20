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

void	handle_redirect_or_text_token(t_token **tokens, int *n_tokens,
	char *token_value)
{
	if (*n_tokens > 1 && (tokens[*n_tokens - 2]->type == T_INPUT
			|| tokens[*n_tokens - 2]->type == T_OUTPUT
			|| tokens[*n_tokens - 2]->type == T_OUTPUT_APPEND
			|| tokens[*n_tokens - 2]->type == T_HEREDOC))
		tokens[(*n_tokens)++] = create_token(T_REDIRECT_ARG, token_value,
				false);
	else
		tokens[(*n_tokens)++] = create_token(T_TEXT, token_value, false);
}

void	add_token_and_free(t_token **tokens, int *n_tokens, t_token_type type,
	char *value)
{
	tokens[(*n_tokens)++] = create_token(type, value, false);
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
	data->tokens[data->num_tokens] = create_token(T_REDIRECT_ARG, *start, true);
	if (!data->tokens[data->num_tokens])
		return (1);
	data->num_tokens++;
	*end = temp;
	*start = end;
	return (0);
}
