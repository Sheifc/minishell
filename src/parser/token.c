#include "token.h"

t_token	*create_token(t_token_type type, const char *value, bool expect_arg,
	t_shell *data)
{
	t_token	*token;

	token = (t_token *)malloc(sizeof(t_token));
	if (!token)
	{
		if (data)
			ft_error(E_MEMORY, NULL, &data->status);
		else
			ft_error(E_MEMORY, NULL, NULL);
		return (NULL);
	}
	token->type = type;
	token->value = ft_strdup(value);
	token->expect_arg = expect_arg;
	return (token);
}

void	free_token(t_token **token)
{
	if (*token)
	{
		if ((*token)->value)
			free((*token)->value);
		free(*token);
	}
	*token = NULL;
}

t_token	**process_tokens(t_shell *data, char *input_copy)
{
	char	*start;

	start = input_copy;
	while (*start)
	{
		skip_delimiters(&start);
		if (!*start)
			break ;
		if (*start == '"' || *start == '\'')
			handle_quotes(&start, data, *start);
		else if (handle_regular_tokens(&start, data) != 0)
			return (NULL);
	}
	return (data->tokens);
}

t_token	**tokenize(t_shell *data)
{
	char			*input_copy;
	char			*input;
	t_word_features	feat;

	feat.start = 0;
	feat.pos = -1;
	feat.btw_quotes = false;
	feat.new_word = true;
	input = preprocess_input(data->prompt, feat, data);
	data->tokens = (t_token **)malloc(MAX_TOKENS * sizeof(t_token *));
	if (!data->tokens)
	{
		ft_error(E_MEMORY, NULL, &data->status);
		return (NULL);
	}
	data->num_tokens = 0;
	input_copy = ft_strdup(input);
	free(input);
	if (process_tokens(data, input_copy) == NULL)
	{
		free(input_copy);
		return (NULL);
	}
	free(input_copy);
	return (data->tokens);
}
