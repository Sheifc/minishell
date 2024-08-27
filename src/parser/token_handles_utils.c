/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_handles_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sheferna <sheferna@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 18:47:49 by sheferna          #+#    #+#             */
/*   Updated: 2024/08/27 18:47:50 by sheferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"

int	handle_token(char **start, t_shell *data, t_token_type type, char *value)
{
	if (add_token(start, data, (t_token){type, value, true}) != 0)
		return (1);
	return (handle_redirect_arg(start, data));
}

bool	process_char(const char *input, int *i, char *quote_char)
{
	if (*quote_char == '\0')
	{
		*quote_char = input[*i];
		(*i)++;
		return (true);
	}
	else if (input[*i] == *quote_char)
	{
		*quote_char = '\0';
		(*i)++;
		return (true);
	}
	return (false);
}

char	*parse_string(const char *input, t_shell *data)
{
	char	*result;
	int		i;
	int		j;
	char	quote_char;

	result = (char *)malloc((ft_strlen(input) + 1) * sizeof(char));
	if (!result)
		return (ft_error(E_MEMORY, NULL, &data->status));
	quote_char = '\0';
	i = 0;
	j = 0;
	while (i < (int)ft_strlen(input))
	{
		if (input[i] == '"' || input[i] == '\'')
		{
			if (!process_char(input, &i, &quote_char))
				result[j++] = input[i++];
		}
		else
			result[j++] = input[i++];
	}
	result[j] = '\0';
	return (result);
}

int	add_redirect_token(t_shell *data, char **start, char *end)
{
	char	temp;
	char	*value;
	char	*clean_value;

	temp = *end;
	*end = '\0';
	if (is_wildcards(start))
		return (handle_wildcards(start, data, T_REDIRECT_ARG));
	value = ft_strndup(*start, end - *start + 1);
	clean_value = parse_string(value, data);
	free(value);
	data->tokens[data->num_tokens] = create_token(T_REDIRECT_ARG, clean_value,
			true, data);
	free(clean_value);
	if (!data->tokens[data->num_tokens])
		return (1);
	data->num_tokens++;
	*end = temp;
	*start = end;
	return (0);
}
