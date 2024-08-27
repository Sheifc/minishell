/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sheferna <sheferna@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 18:47:08 by sheferna          #+#    #+#             */
/*   Updated: 2024/08/27 18:47:09 by sheferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	only_spaces(char *prompt)
{
	int	i;

	i = 0;
	while (prompt[i])
	{
		if (prompt[i] != ' ' && prompt[i] != '\t')
			return (0);
		i++;
	}
	return (1);
}

int	only_wildcard(char *prompt)
{
	int	i;

	i = 0;
	while (prompt[i])
	{
		if (prompt[i] != ' ' && prompt[i] != '\t' && prompt[i] != '*'
			&& prompt[i] != '?')
			return (0);
		i++;
	}
	return (1);
}
