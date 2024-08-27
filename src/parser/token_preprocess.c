/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_preprocess.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sheferna <sheferna@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 18:48:02 by sheferna          #+#    #+#             */
/*   Updated: 2024/08/27 18:48:03 by sheferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"

char	*process_word(const char *input, int start, int length, char *output)
{
	char	*word;

	word = get_converted_word(input + start, length);
	output = ft_strcat(output, word);
	output = ft_strcat(output, " ");
	free(word);
	return (output);
}

int	get_operation_size(const char *str)
{
	if (ft_strncmp(str, "&&", 2) == 0 || ft_strncmp(str, "||", 2) == 0)
		return (2);
	if (ft_strncmp(str, "<<", 2) == 0 || ft_strncmp(str, ">>", 2) == 0)
		return (2);
	if (ft_strncmp(str, ">", 1) == 0 || ft_strncmp(str, "<", 1) == 0)
		return (1);
	if (ft_strncmp(str, "|", 1) == 0 || ft_strncmp(str, ";", 1) == 0
		|| ft_strncmp(str, "(", 1) == 0 || ft_strncmp(str, ")", 1) == 0)
		return (1);
	return (0);
}

void	handle_character(const char *in, char **output, t_word_features *ft)
{
	if (in[ft->pos] == '"' || in[ft->pos] == '\'')
		toggle_between_quotes(ft);
	else if (get_operation_size(&in[ft->pos]) && !ft->btw_quotes
		&& ft->new_word)
	{
		process_word(in, ft->pos, get_operation_size(&in[ft->pos]), *output);
		ft->new_word = true;
		ft->pos = ft->pos + get_operation_size(&in[ft->pos]) - 1;
		ft->start = ft->pos;
	}
	else if ((in[ft->pos] == ' ' || get_operation_size(&in[ft->pos]))
		&& !ft->btw_quotes)
		handle_spaces_and_operators(in, output, ft);
	else
	{
		if (ft->new_word)
		{
			ft->start = ft->pos;
			ft->new_word = false;
		}
	}
}

void	update_quote_state(char c, bool *in_single_quote, bool *in_double_quote,
		int *count)
{
	if (c == '\'' && !(*in_double_quote))
	{
		*in_single_quote = !(*in_single_quote);
		(*count)++;
	}
	else if (c == '"' && !(*in_single_quote))
	{
		*in_double_quote = !(*in_double_quote);
		(*count)++;
	}
}

int	count_quotes(const char *str)
{
	int		i;
	int		count;
	bool	in_single_quote;
	bool	in_double_quote;

	i = 0;
	count = 0;
	in_single_quote = false;
	in_double_quote = false;
	while (str[i] != '\0')
	{
		update_quote_state(str[i], &in_single_quote, &in_double_quote, &count);
		i++;
	}
	return (count);
}
