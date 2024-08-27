/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sheferna <sheferna@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 18:48:15 by sheferna          #+#    #+#             */
/*   Updated: 2024/08/27 18:48:16 by sheferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
		if (handle_regular_tokens(&start, data) != 0)
		{
			free_tokens(&data->tokens, &data->num_tokens);
			return (NULL);
		}
	}
	return (data->tokens);
}

t_token	**tokenize(t_shell *data)
{
	char	*input;

	if (count_quotes(data->prompt) % 2 != 0)
		return (ft_error(E_SYNTAX, "invalid number of quotes", &data->status));
	data->tokens = (t_token **)malloc(MAX_TOKENS * sizeof(t_token *));
	if (!data->tokens)
	{
		ft_error(E_MEMORY, NULL, &data->status);
		return (NULL);
	}
	data->num_tokens = 0;
	input = ft_strdup(data->prompt);
	if (process_tokens(data, input) == NULL)
	{
		free(input);
		return (NULL);
	}
	free(input);
	return (data->tokens);
}
