/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enviroment_check.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sheferna <sheferna@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 18:46:32 by sheferna          #+#    #+#             */
/*   Updated: 2024/08/27 18:46:33 by sheferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"

bool	check_opening_quotes(const char *str, const char *pos)
{
	int			in_single_quote_o;
	int			in_double_quote;
	const char	*start;

	in_single_quote_o = 0;
	in_double_quote = 0;
	start = str;
	while (*start && start < pos)
	{
		if (*start == '\'' && !in_double_quote)
			in_single_quote_o = !in_single_quote_o;
		else if (*start == '"' && !in_single_quote_o)
			in_double_quote = !in_double_quote;
		start++;
	}
	if (in_double_quote)
		return (false);
	return (in_single_quote_o);
}

bool	check_closing_quotes(const char *str, const char *pos,
		bool in_single_quote_o)
{
	int			in_single_quote_c;
	int			in_double_quote;
	const char	*end;

	(void)str;
	in_single_quote_c = 0;
	in_double_quote = 0;
	end = pos;
	while (*end && *end != '\0')
	{
		if (*end == '\'' && !in_double_quote)
		{
			in_single_quote_c = !in_single_quote_c;
			break ;
		}
		else if (*end == '"' && !in_single_quote_c && !in_single_quote_o)
			in_double_quote = !in_double_quote;
		end++;
	}
	return (in_single_quote_c);
}

bool	is_btw_single_quotes(const char *str, const char *pos)
{
	bool	is_open_quote;
	bool	is_close_quote;

	is_open_quote = check_opening_quotes(str, pos);
	is_close_quote = check_closing_quotes(str, pos, is_open_quote);
	return (is_open_quote && is_close_quote);
}
