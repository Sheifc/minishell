/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sheferna <sheferna@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 18:48:21 by sheferna          #+#    #+#             */
/*   Updated: 2024/08/27 18:48:22 by sheferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"

// Main function for pattern matching
int	match(const char *pattern, const char *string)
{
	if (*pattern == '\0' && *string == '\0')
		return (0);
	if (*pattern == '\0')
		return (NOMATCH);
	if (*pattern == '?' && ((*(pattern - 1) != ' ' && *(pattern + 1)
				&& *(pattern + 1) != ' ') || (*(pattern - 1) != ' '
				&& !*(pattern + 1))))
		return (handle_question(pattern, string));
	else if (*pattern == '*')
		return (handle_star(pattern, string));
	else if (*pattern == '[')
		return (handle_brackets(pattern, string));
	else
		return (handle_exact_match(pattern, string));
}

// Wrapper function for pattern matching
static int	found_match(const char *pattern, const char *string)
{
	if (match(pattern, string) == 0)
		return (0);
	return (NOMATCH);
}

int	process_directory_entries(DIR *dir, const char *wildcard, t_shell *d,
		t_token_type t)
{
	struct dirent	*entry;
	int				found;
	char			*clean_wildcard;

	found = 0;
	entry = readdir(dir);
	clean_wildcard = remove_repeated_chars(wildcard, '*');
	while (entry != NULL)
	{
		if (found_match(clean_wildcard, entry->d_name) == 0)
		{
			found = 1;
			d->tokens[d->num_tokens] = create_token(t, entry->d_name, true, d);
			if (!d->tokens[d->num_tokens])
			{
				free(clean_wildcard);
				return (-1);
			}
			d->num_tokens++;
		}
		entry = readdir(dir);
	}
	free(clean_wildcard);
	closedir(dir);
	return (found);
}

// Function to search for matches in the current directory
int	search_wildcard_matches(const char *wildcard, t_shell *data,
		t_token_type type)
{
	DIR	*dir;

	dir = opendir(".");
	if (dir == NULL)
	{
		ft_error(E_FILE, NULL, &data->status);
		return (-1);
	}
	return (process_directory_entries(dir, wildcard, data, type));
}

// Function to check if the word is a wildcard
bool	is_wildcards(char **start)
{
	char	*end;

	end = *start;
	while (*end && !ft_strchr(" \r\n\t\v\f\"'()|<>;&", *end))
	{
		if ((*end == '*' || *end == '?' || *end == '[' || *end == ']')
			&& (*(end - 1) && *(end -1) != '$'))
			return (true);
		end++;
	}
	return (false);
}
