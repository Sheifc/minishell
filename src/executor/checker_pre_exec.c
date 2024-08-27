/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_pre_exec.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sheferna <sheferna@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 19:20:46 by sheferna          #+#    #+#             */
/*   Updated: 2024/08/23 20:21:52 by sheferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_invalid_ampersand(char *arg)
{
	if (arg[0] == '&' && arg[1] == '\0')
		return (1);
	return (0);
}

int	is_invalid_dot_usage(char *arg)
{
	if (arg[0] == '.')
	{
		if (arg[1] == '\0' || ft_isalpha(arg[1]) || arg[1] == '.'
			|| (arg[1] == '/' && (arg[2] == '\0') && !ft_isalpha(arg[2])))
			return (1);
	}
	return (0);
}

int	is_invalid_slash(char *arg)
{
	if (arg[0] == '/' && arg[1] == '\0')
		return (1);
	return (0);
}

int	is_special_char(char c)
{
	if ((c >= 33 && c <= 37) || c == 39 || (c >= 43 && c <= 45) || (c >= 58
			&& c <= 59) || c == 61 || (c == 64) || (c >= 91 && c <= 96)
		|| c == 123 || c == 125 || c == 126 || ((unsigned char)c >= 128
			&& (unsigned char)c < 255))
		return (1);
	return (0);
}

int	checker(t_shell *data, t_cmd *cmd)
{
	t_cmd	*current;
	char	*arg;

	current = cmd;
	while (current)
	{
		if (current->arg == NULL || current->arg[0] == NULL)
		{
			ft_putendl_fd("minishell: argument is NULL", 2);
			data->status = 2;
			return (1);
		}
		arg = current->arg[0];
		if (is_special_char(arg[0]) || is_invalid_slash(arg)
			|| is_invalid_dot_usage(arg) || is_invalid_ampersand(arg))
		{
			printf("minishell: syntax error near unexpected token `%s'\n", arg);
			data->status = 2;
			return (1);
		}
		current = current->next;
	}
	return (0);
}
