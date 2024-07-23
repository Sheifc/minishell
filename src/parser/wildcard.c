#include "token.h"

// Main function for pattern matching
int	match(const char *pattern, const char *string)
{
	if (*pattern == '\0' && *string == '\0')
		return (0);
	if (*pattern == '\0')
		return (NOMATCH);
	if (*pattern == '?')
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

// Function to search for matches in the current directory
bool	search_wildcard_matches(const char *wildcard, Token **tokens,
	int *n_tokens)
{
	DIR				*dir;
	struct dirent	*entry;
	bool			found;

	dir = opendir(".");
	if (dir == NULL)
	{
		perror("opendir");
		return (false);
	}
	found = false;
	entry = readdir(dir);
	while (entry != NULL)
	{
		if (found_match(wildcard, entry->d_name) == 0)
		{
			found = true;
			tokens[*n_tokens] = create_token(T_ARG, entry->d_name, true);
			(*n_tokens)++;
		}
		entry = readdir(dir);
	}
	closedir(dir);
	return (found);
}

// Function to check if the word is a wildcard
bool	is_wildcards(char **start)
{
	char	*end;

	end = *start;
	while (*end && !strchr(" \r\n\t\v\f\"'()|<>;&", *end))
	{
		if (*end == '*' || *end == '?' || *end == '[' || *end == ']')
			return (true);
		end++;
	}
	return (false);
}
