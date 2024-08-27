/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sheferna <sheferna@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 18:46:44 by sheferna          #+#    #+#             */
/*   Updated: 2024/08/27 18:46:46 by sheferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error.h"

char	*str_error(int ecode)
{
	if (ecode == E_FILE)
		return ("Input/Output");
	else if (ecode == E_SYNTAX)
		return ("Syntax");
	else if (ecode == E_MEMORY)
		return ("Memory");
	else if (ecode == E_REDIRECT)
		return ("Redirect");
	else if (ecode == E_COMMAND)
		return ("minishell");
	return ("Unknown");
}

void	*ft_error(const int error_code, const char *message, int *status)
{
	if ((message == NULL || ft_strlen(message) == 0) && error_code <= 0)
		ft_fprintf(STDERR_FILENO, "\e[31m minishell(%d): %s\e[0m\n",
			errno, strerror(errno));
	else if (error_code <= 0)
		ft_fprintf(STDERR_FILENO, "\e[31m minishell(%d): %s\e[0m\n",
			errno, message);
	else if (message == NULL || ft_strlen(message) == 0)
		ft_fprintf(STDERR_FILENO, "\e[31m %s error(%d): %s\e[0m\n",
			str_error(error_code), error_code, strerror(errno));
	else
		ft_fprintf(STDERR_FILENO, "\e[31m minishell(%d): %s\e[0m\n", error_code,
			message);
	if (status != NULL && error_code <= 0)
		*status = errno;
	else if (status != NULL)
		*status = error_code;
	return (NULL);
}

void	*ft_error_ope(const int error_code, char *ope, const char *message,
		int *status)
{
	if ((message == NULL || ft_strlen(message) == 0) && error_code <= 0)
		ft_fprintf(STDERR_FILENO, "\e[31m minishell(%d): \'%s\' %s\e[0m\n",
			errno, ope, strerror(errno));
	else if (error_code <= 0)
		ft_fprintf(STDERR_FILENO, "\e[31m minishell(%d): \'%s\' %s\e[0m\n",
			errno, ope, message);
	else if (message == NULL || ft_strlen(message) == 0)
		ft_fprintf(STDERR_FILENO, "\e[31m %s error(%d): \'%s\' %s\e[0m\n",
			str_error(error_code), error_code, ope, strerror(errno));
	else
		ft_fprintf(STDERR_FILENO, "\e[31m %s error(%d): \'%s\' %s\e[0m\n",
			str_error(error_code), error_code, ope, message);
	if (status != NULL && error_code <= 0)
		*status = errno;
	else if (status != NULL)
		*status = error_code;
	return (NULL);
}

void	*ft_error_syntax(const int error_code, char *ope, const char *message,
		int *status)
{
	ft_fprintf(STDERR_FILENO, "\e[31m minishell(%d): %s \'%s\'\e[0m\n",
		error_code, message, ope);
	if (status != NULL && error_code <= 0)
		*status = errno;
	else if (status != NULL)
		*status = error_code;
	return (NULL);
}
