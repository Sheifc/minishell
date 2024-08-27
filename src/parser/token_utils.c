/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sheferna <sheferna@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 18:48:07 by sheferna          #+#    #+#             */
/*   Updated: 2024/08/27 18:48:08 by sheferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"

void	free_tokens(t_token ***tokens, int *num_tokens)
{
	int	i;

	if (*tokens == NULL)
		return ;
	i = -1;
	while (++i < *num_tokens)
		free_token(&(*tokens)[i]);
	free(*tokens);
	*tokens = NULL;
	*num_tokens = 0;
}

void	skip_delimiters(char **start)
{
	while (**start && ft_strchr(DELIMITERS, **start))
		(*start)++;
}

int	add_token(char **start, t_shell *data, t_token t)
{
	data->tokens[data->num_tokens] = create_token(t.type, t.value, t.expect_arg,
			data);
	if (!data->tokens[data->num_tokens])
		return (1);
	data->num_tokens++;
	*start += ft_strlen(t.value);
	return (0);
}

int	add_cmd_arg_token(char **start, t_shell *data)
{
	char			*end;
	char			temp;
	t_token_type	type;

	handle_quotes(start, &end);
	temp = *end;
	*end = '\0';
	if (data->num_tokens > 0 && data->tokens[data->num_tokens - 1]->expect_arg)
		type = T_ARG;
	else
		type = T_COMMAND;
	data->tokens[data->num_tokens] = create_token(type, *start, true, data);
	if (!data->tokens[data->num_tokens])
		return (1);
	data->num_tokens++;
	*end = temp;
	*start = end;
	return (0);
}

void	print_tokens(t_token **tokens, int n_tokens)
{
	int	i;

	i = -1;
	while (tokens && ++i < n_tokens)
		printf("Token %d: Type = %d, Value = %s (%lu)\n", i, tokens[i]->type,
			tokens[i]->value, ft_strlen(tokens[i]->value));
}
