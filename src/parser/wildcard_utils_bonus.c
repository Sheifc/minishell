/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_utils_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sheferna <sheferna@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 18:48:29 by sheferna          #+#    #+#             */
/*   Updated: 2024/08/27 18:48:30 by sheferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"

// Function to check if a character is within a character set
int	char_in_set(char c, const char *set)
{
	while (*set && *set != ']')
	{
		if (*set == c)
			return (1);
		set++;
	}
	return (0);
}

// Function to handle the case of the '?' wildcard
int	handle_question(const char *pattern, const char *string)
{
	if (*string != '\0')
		return (match(pattern + 1, string + 1));
	else
		return (NOMATCH);
}

// Function to handle the case of the '*' wildcard
int	handle_star(const char *pattern, const char *string)
{
	if (match(pattern + 1, string) == 0)
		return (0);
	if (*string != '\0')
		return (match(pattern, string + 1));
	else
		return (NOMATCH);
}

// Function to handle the case of square brackets '[' and ']'
int	handle_brackets(const char *pattern, const char *string)
{
	const char	*end;

	end = ft_strchr(pattern + 1, ']');
	if (end == NULL)
		return (NOMATCH);
	if (char_in_set(*string, pattern + 1))
		return (match(end + 1, string + 1));
	else
		return (NOMATCH);
}

// Function to handle exact character matching
int	handle_exact_match(const char *pattern, const char *string)
{
	if (*pattern == *string)
		return (match(pattern + 1, string + 1));
	else
		return (NOMATCH);
}
