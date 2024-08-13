#include "token.h"

t_token	*create_token(t_token_type type, const char *value, bool expect_arg)
{
	t_token	*token;

	token = (t_token *)malloc(sizeof(t_token));
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
			handle_quotes(&start, data->tokens, &data->num_tokens, *start);
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
