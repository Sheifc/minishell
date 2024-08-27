/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_verify.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sheferna <sheferna@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 18:48:11 by sheferna          #+#    #+#             */
/*   Updated: 2024/08/27 18:48:12 by sheferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"

int	verify_parentheses(t_shell *data)
{
	int	balance;
	int	i;

	i = -1;
	balance = 0;
	while (data->tokens && ++i < data->num_tokens)
	{
		if (data->tokens[i]->type == T_PAREN_OPEN)
			balance++;
		else if (data->tokens[i]->type == T_PAREN_CLOSE)
			balance--;
		if (balance < 0)
		{
			ft_error_syntax(E_SYNTAX, ")", "syntax error near unexpected token",
				&data->status);
			return (1);
		}
	}
	if (balance > 0)
	{
		ft_error_syntax(E_SYNTAX, "(", "syntax error near unexpected token",
			&data->status);
		return (1);
	}
	return (0);
}

int	verify_quotes(t_shell *data)
{
	int	balance;
	int	i;

	i = -1;
	balance = 0;
	while (data->tokens && ++i < data->num_tokens)
	{
		if (data->tokens[i]->type == T_QUOTE)
			balance++;
	}
	if (balance % 2 != 0)
	{
		ft_error(E_SYNTAX, "invalid number of quotes", &data->status);
		return (1);
	}
	return (0);
}

int	verify_redirection(t_shell *data)
{
	int	i;

	i = -1;
	while (data->tokens && ++i < data->num_tokens)
	{
		if (data->tokens[i]->type == T_REDIRECT_ARG
			&& (ft_strcmp(data->tokens[i]->value, ">") == 0
				|| ft_strcmp(data->tokens[i]->value, "<") == 0))
		{
			ft_error_syntax(E_SYNTAX, data->tokens[i]->value,
				"syntax error near unexpected token", &data->status);
			return (1);
		}
	}
	return (0);
}

int	verify_tokens(t_shell *data)
{
	if (verify_parentheses(data) || verify_quotes(data)
		|| verify_redirection(data))
		return (1);
	return (0);
}
